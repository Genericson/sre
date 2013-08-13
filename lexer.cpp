#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "lexer.hpp"

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
bool Token::operator!= ( Token rarg ) {
    return ( this->type  != rarg.type);
}
bool Token::operator!= ( Token::TOKEN type ) {
    return (this->type != type);
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
        case END_OF_INPUT: return "end-of-input";
        case ERROR: return "token error";
        default: return "missing token identifier";
    }
}

//== Lexer ==//
    //// ctor ////
Lexer::Lexer ( const Lexer& lex) {
    this->input = new std::istringstream(lex.input->str());
    this->ch = ' ';
}
Lexer::Lexer ( std::string input ) {
    this->input = new std::istringstream(input);
    this->ch = ' ';
}
    //// dtor ////
Lexer::~Lexer () {
    delete (this->input);
}
    //// state methods ////
void Lexer::space () {
    while( input->good() && std::isspace(ch)) {
        ch = this->input->get();
    }
}
Token Lexer::identifier () {
    std::string str = "";
    do {
        str.push_back(ch);
        ch = this->input->get();
    } while ( input->good() && isalnum(ch) );          // [a-zA-Z0-9]
    return Token(Token::IDENTIFIER, str);
}
Token Lexer::numLit () {
    std::string str = "";
    do {
        str.push_back(ch);
        ch = this->input->get();
    } while ( input->good() && isdigit(this->ch));
    if (ch == '.' ) {        // [.] /// decimal point
        return floatLit(str);   // must be a float liter
    }
    else if ( std::isalpha(ch) )
        return Token(Token::ERROR, "invalid character after number");
    else {
        return(Token(Token::INT_LIT, str));     // must be an int literal
    }
}
Token Lexer::floatLit (std::string lh) {
    std::string str = lh;
    str.push_back(ch);
    ch = this->input->get();
    if (!std::isdigit(ch)) {
        str.push_back('0');

    }
    while ( input->good() && std::isdigit(ch)) {
        str.push_back(ch);
        ch = this->input->get();
    }
    if ( std::isalpha(ch) )
        return Token(Token::ERROR, "invalid character after number");
    else
        return Token(Token::FLOAT_LIT, str);
}
Token Lexer::charLit () {
    std::string str = "";
   ch = this->input->get();
    if ( input->good() && ch == '\'') { //empty can only be a string literal
        ch = this->input->get();
        return Token(Token::STRING_LIT, str);
    }
    if ( input->good() && ch != '\'') {
        str.push_back(ch);
        ch = this->input->get();
    }
    if ( ch == '\'' ) {     // terminating single quote
        ch = this->input->get();
        return Token(Token::CHAR_LIT, str);
    } else if ( input->good() ) {
        return stringLit(str);
    } else {
        return Token(Token::ERROR,
                     "character literal missing end [\']");
    }
}
Token Lexer::stringLit (std::string lh) {
    std::string str = lh;
    do  {
        str.push_back(ch);
        ch = this->input->get();
    } while ( input->good() && ch != '\'');
    if( ch == '\'') {        // terminating single quote
        ch = this->input->get();
        return Token(Token::STRING_LIT, str);
    } else {
        return Token(Token::ERROR,
                     "string literal missing end [\']");
    }
}
Token Lexer::separator () {
    std::string str;
    str.push_back(ch);
    ch = this->input->get();
    return Token(Token::SEPARATOR, str);
}


/** Get next token
 *  \return The next token from the Lexer's inputstream**/
Token Lexer::next () {
        // skip white space
         if (std::isspace(ch)) {     // [ \f\n\r\t\v]
            space();
        }

        if ( ch == EOF ) {
            return Token(Token::END_OF_INPUT);
        }
        // is identifier
        else if (std::isalpha(ch)) {     // [a-zA-Z]
            return identifier();
        }
        // is numeric literal
        else if (std::isdigit(ch)) {     // [0-9]
            return numLit();
        }
        else if (ch == '.') {
            return floatLit("0");
        }
        // is char or string literal
        else if (ch == '\'') {
            return charLit();
        }
        // is separator
        else if (ch == ';' || ch == ',') {
            return separator();
        }
        else {
            std:: string str = "invalid character [";
            str.push_back(ch);
            str.append("] for token");
            return Token(Token::ERROR, str);
        }
}


}
}
