#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED

namespace sre {
namespace console {

class Token
{
public:
        //// data members ////
    enum TOKEN {
        IDENTIFIER,
        SEPARATOR,
        INT_LIT,
        FLOAT_LIT,
        CHAR_LIT,
        STRING_LIT,
        END_OF_INPUT, // end of input (or end of file)
        ERROR // special token that represents an error occured
    };
    TOKEN type;
    std::string value;
        //// methods ////
    Token () {}
    Token ( TOKEN type );
    Token ( TOKEN type, std::string value );
    std::string toString ();
    bool operator== ( Token rarg );
    bool operator== ( Token::TOKEN id );
    bool operator!= ( Token rarg );
    bool operator!= ( Token::TOKEN id );
    bool isError() { if(type == Token::ERROR) return true; };
        //// static methos ////
    std::string name();
};

class Statement;
class Command;
class Args;
class Arg;
class TermSym;

class Lexer
{
private:
    std::istringstream * input;
    char ch;

    //// methods representing states in DFSA ////
    void space ();
    Token identifier ();
    Token numLit ();
    Token floatLit (std::string lh);
    Token charLit ();
    Token stringLit (std::string lh);
    Token separator ();


public:
    Lexer (const Lexer& lex);
    Lexer ( std::string input );
    Token next ();
    ~Lexer();
};

class Parser;

class Translator;

} // namespace console
} // namespace sre


#endif // COMPILER_HPP_INCLUDED
