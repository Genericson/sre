#ifndef SRE_COMMAND_HPP
#define SRE_COMMAND_HPP

#include <list>

namespace sre { namespace console {

class CommandFunc;
class CommandDef;
class Command;
class Value;
class Type;
class Arg;
using TypeList = std::list<Type>;

class CommandDef
{
private:
    std::string id;
    std::unique_ptr<TypeList> parameters;
    std::shared_ptr<CommandFunc> func;
public:
    CommandDef (const CommandDef& cmdDef);
    CommandDef (std::string id);
    void push (Type type);
    void setFunc (std::shared_ptr<CommandFunc> cmdFunc);
    std::string operator() (Command cmd);
    std::string getId() {return id;}

    friend bool operator== (const Command& cmd, const CommandDef& def);
    friend bool operator== (const CommandDef& def, const Command& cmd);
};

class Command
{
private:
    std::string id;
    std::unique_ptr<TypeList> args;
public:
    Command(std::string id);
    void push(Type type);

    friend bool operator==(const Command& cmd, const CommandDef& def);
    friend bool operator==(const CommandDef& def, const Command& cmd);
};

class CommandFunc {
public:
    CommandFunc () {}
    virtual std::string operator() (const Command& cmd) =0;
};

class EmptyCommand : public CommandFunc {
public:
    std::string operator() (const Command& cmd) { return "Did nothing."; }
};

//class EchoCommand : public CommandFunc {
//    void operator() (Command cmd);
//};

class Type
{
private:
    std::string id;
public:
    Type (std::string id);
    Type (const Type & type);
    Type & operator= (const Type & type);

    friend bool operator==(const Command& cmd, const CommandDef& def);
    friend bool operator==(const CommandDef& def, const Command& cmd);
};

class Arg
{
private:
    std::unique_ptr<Type> type;
    std::string value;
public:
    Arg(const Type& type, std::string value);
    std::string getVal() { return value; }
    Type getType() { return *type; }

};

//// namespace functions ////

bool operator==(const Command& cmd, const CommandDef& def);
bool operator==(const CommandDef& def, const Command& cmd);

}} // namespace


#endif // SRE_COMMAND_HPP
