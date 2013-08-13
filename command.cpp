//#include <functional>

//temp
#include <iostream>

#include <string>
#include <list>
#include <memory>
#include <functional>
#include "variable.hpp"
#include "command.hpp"

namespace sre { namespace console {

//== CommandFunc ==//
/** \class CommandFunc
 * This is a functor class designed to be used with CommandDef.
 * Any inherited class can be used with CommandDef that defines `operator()(const Command&)`.
 * \warning The parameters of the CommandFunc must correlate with those of the CommandDef. **/
//== other CommandFunc children ==//
/** \class EmptyCommand
 *  A functor that does nothing **/
/** \class EchoCommand
 *  A functor that echoes it's argument **/
////
//void EchoCommand::operator() (Command cmd) {
//}



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
    parameters->push_back(type);
}
/** Calls this Command's associated functor by passing it a Command (along with it's associated arguments).
 *  **/
void CommandDef::operator() (Command cmd) {
}
//== Command ==//
    //// ctor ////
Command::Command(std::string id) {
    this->id = id;
    args = std::unique_ptr<TypeList>(new TypeList());
}
void Command::push(Type type) {
    args->push_back(type);
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
        auto itArg = argList.begin();
        auto itDef = paramList.begin();
        // for each parameter
        for(; itArg != argList.end(); ++itArg, ++itDef ) {
            if ( itDef == paramList.end() ) { // too many arguments
                std::cerr<<"too many arguments"<<std::endl;
                return false;
            }
            else if ( itArg->id != itDef->id ) { // wrong type
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
bool operator==(const CommandDef& def, const Command& cmd) {
    return (cmd == def);
}

}} // namespace
