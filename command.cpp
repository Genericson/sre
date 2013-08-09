//#include <functional>

//temp
#include <iostream>

#include <string>
#include <forward_list>
#include <memory>
#include "command.hpp"

namespace sre { namespace console {

//== CommandDef ==//
/** \class CommandDef
 *  A definition for a command **/
CommandDef::CommandDef( std::string id)
{
    // no parameters by default
    this->id = id;
    parameters = std::unique_ptr<TypeList>(new TypeList());
}
/** Push a new parameter to the list of parameters
 *  \param[in] type Type of parameter **/
void CommandDef::push(Type type) {
    parameters->push_front(type);
}
//== Command ==//
    //// ctor ////
Command::Command(std::string id) {
    this->id = id;
    args = std::unique_ptr<TypeList>(new TypeList());
}
void Command::push(Type type) {
    args->push_front(type);
}
//== Type ==//
    //// ctor ////
Type::Type(std::string id) {
    this->id = id;
}
Type::Type (const Type & type) {
    *this = type;
}
    //// asignment ////
Type& Type::operator= (const Type & type) {
    this->id = type.id;
    return *this;
}
//== Arg ==//
    //// ctor ////
Arg::Arg(const Type& type, std::string value) {
    this->type = std::unique_ptr<Type>(new Type(type));
    this->value = value;
}

/////////////// namespace functions ////////////////
bool operator==(const Command& cmd, const CommandDef& def) {
    TypeList& argList = *cmd.args;
    TypeList& paramList = *def.parameters;
    if (cmd.id == def.id)
    {
        if(argList.empty() && paramList.empty())
        {
            return true;
        }
        auto itDef = paramList.begin();
        // for each parameter
        for(Type& arg : argList) {
            if ( itDef == paramList.end() ) { // too many arguments
                return false;
                std::cerr<<"too many arguments"<<std::endl;
            }
            else if ( arg.id != itDef->id ) { // wrong type
                std::cerr<<"wrong type"<<std::endl;
                return false;
            }
        }
        if (itDef != paramList.end()) { // not enough arguments
            std::cerr<<"not enough arguments"<<std::endl;
            return false;
        }
        else
            return true;
    } else {
        return false;
    }
}
inline bool operator==(const CommandDef& def, const Command& cmd) {
    return (cmd == def);
}

}} // namespace
