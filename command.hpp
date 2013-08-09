#ifndef SRE_COMMAND_HPP
#define SRE_COMMAND_HPP

#include <forward_list>

namespace sre { namespace console {

class CommandDef;
class Command;
class Type;
class Arg;
using TypeList = std::forward_list<Type>;

class CommandDef
{
private:
    std::string id;
    std::unique_ptr<TypeList> parameters;
public:
    CommandDef(std::string id);
    void push(Type type);

    friend bool operator==(const Command& cmd, const CommandDef& def);
    friend bool operator==(const CommandDef& def, const Command& cmd);
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

};

//// namespace functions ////

bool operator==(const Command& cmd, const CommandDef& def);
inline bool operator==(const CommandDef& def, const Command& cmd);

}} // namespace


#endif // SRE_COMMAND_HPP
