#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "compiler.hpp"

namespace sre {
namespace console
{
//== Token ==//
Token::Token ( TOKEN type ) {
    this->type = type;
    this->value = "";
}
Token::Token ( TOKEN type, std::string value ) {
    this->type = type;
    this->value = value;
}
std::string Token::toString () {
    return value;
}
bool Token::operator== ( Token rarg ) {
    return ( this->type  == rarg.type);
}
bool Token::operator== ( Token::TOKEN type ) {
    return (this->type == type);
}
std::string Token::name () {
    switch(type)
    {
        case IDENTIFIER: return "identifier";
        case SEPARATOR: return "separator";
        case INT_LIT: return "integer literal";
        case FLOAT_LIT: return "float literal";
        case CHAR_LIT: return "character literal";
        case STRING_LIT: return "string literal";
        case ERROR: return "token error";
        default: return "missing token identifier";
    }
}

//== Lexer ==//
    //// ctor ////
Lexer::Lexer ( std::string input ) {
    this->input = new std::istringstream(input);
}
    //// dtor ////
Lexer::~Lexer () {
    delete (this->input);
}
    //// state methods ////
void Lexer::space () {
    while(std::isspace(this->ch)) {
        this->input->get(this->ch);
    }
}
Token Lexer::identifier () {
    std::string str = "";
    do {
        str.push_back(ch);
        this->input->get(this->ch);
    } while (isalnum(this->ch));          // [a-zA-Z0-9]
    return Token(Token::IDENTIFIER, str);
}
Token Lexer::numLit () {
    std::string str = "";
    do {
        str.push_back(ch);
        this->input->get(this->ch);
    } while (isdigit(this->ch));
    if (ch == '.' ) {        // [.] /// decimal point
        return floatLit(str);   // must be a float liter
    }
    else
        return(Token(Token::INT_LIT, str));     // must be an int literal
}
Token Lexer::floatLit (std::string lh) {
    std::string str = lh;
    str.push_back(ch);
    this->input->get(ch);
    if (!std::isdigit(ch)) {
        str.push_back('0');

    }
    while (std::isdigit(ch)) {
        str.push_back(ch);
        this->input->get(ch);
    }
    return Token(Token::FLOAT_LIT, str);
}
Token Lexer::charLit () {
    std::string str;
    this->input->get(ch);
    if ( input->good() && ch != '\'') {
        str.push_back(ch);
        this->input->get(ch);
    }
    if ( ch == '\'' ) {     // terminating single quote
        return Token(Token::CHAR_LIT, str);
    } else if ( input->good() ){
        return stringLit(str);
    } else {
        return Token(Token::ERROR,
                     "character literal missing end \[\'\]");
    }
}
Token Lexer::stringLit (std::string lh) {
    std::string str = lh;
    do  {
        str.push_back(ch);
        this->input->get(ch);
    } while ( input->good() && ch != '\'');
    if( ch == '\'') {        // terminating double quote
        return Token(Token::STRING_LIT, str);
    } else {
        return Token(Token::ERROR,
                     "string literal missing end \[\'\]");
    }

}
Token Lexer::separator () {
    std::string str;
    str.push_back(ch);
    return Token(Token::SEPARATOR, str);
}


/** Get next token
 *  \return The next token from the Lexer's inputstream**/
Token Lexer::next () {
    Token tok;
        // skip white space
    if (std::isspace(ch)) {     // [ \f\n\r\t\v]
        space();
    }
    // is identifier
    if (std::isalpha(ch)) {     // [a-zA-Z]
        return identifier();
    }
    // is numeric literal
    if (std::isdigit(ch)) {     // [0-9]
        return numLit();
    }
    if (ch == '.') {
        return floatLit("0");
    }
    // is char or string literal
    if (ch == '\'') {
        return charLit();
    }
    // is separator
    if (ch == ';' || ch == ',') {
        return separator();
    }

    //next char

    std::cout<<"Current char: "<<this->ch<<std::endl;
    std::cin>>ch;
    //check if end of input was reached prematurely
    // temp
}


}
}
