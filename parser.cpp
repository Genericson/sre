
#include <string>
#include <memory>
#include "variable.hpp"
#include "lexer.hpp"
#include "command.hpp"
#include "variable.hpp"
#include "parser.hpp"

namespace sre { namespace console {

//== CommandMap ==//
void CommandMap::add (CommandDef cmdDef) {
    this->insert( std::pair<std::string, CommandDef>(cmdDef.getId(), cmdDef) );
}

Parser::Parser (const Lexer& lex,
        cmdsPtr cmds,
        varsPtr vars)
{
    this->lex = new Lexer(lex);
    this->cmds = cmds;
    this->vars = vars;
}

/** Checks and executes the code contained in the internal lexer and returns console output. **/
/*std::string Parser::operator() (){
}*/

Parser::~Parser()
{
    delete lex;
}

}} // namespaces
