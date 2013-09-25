#ifndef SRE_PARSER_HPP
#define SRE_PARSER_HPP

#include <map>
#include "command.hpp"
#include "variable.hpp"

namespace sre { namespace console {

class Lexer;

class CommandMap : public std::map<std::string, CommandDef>
{
public:
    void add(CommandDef cmdDef);
};

class VariableMap : std::map<std::string, Variable>
{
};

class Parser
{
    using cmdsPtr = std::shared_ptr<CommandMap>;
    using varsPtr = std::shared_ptr<VariableMap>;
    Lexer * lex;
    std::shared_ptr<CommandMap> cmds;
    std::shared_ptr<VariableMap> vars;
public:
    Parser(const Lexer& lex,
           cmdsPtr cmds=cmdsPtr(new CommandMap()),
           varsPtr vars=varsPtr(new VariableMap()) );
    std::string operator() ();

    virtual ~Parser();
};

#endif // SRE_PARSER_HPP

}} // namespaces
