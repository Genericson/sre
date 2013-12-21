
#include <iostream>
#include <string>
#include <memory>
#include "variable.hpp"

namespace sre { namespace console {

//== Variable ==//
    //// ctor ////
Variable::Variable (std::string name, Variable::TYPE type, std::string val)
{
    this->name = name;
    this->type = type;
    this->val = val;
}

void Variable::set (std::string value) {
    if (type==STRING)
        this->val = value;
    else
        std::cerr<<"ERROR: variable is not string type"<<std::endl;
}
void Variable::set (int value) {
    if (type==INT)
        this->val = value;
    else
        std::cerr<<"ERROR: variable is not integer type"<<std::endl;
}
void Variable::set (float value) {
    if (type==FLOAT)
        this->val = value;
    else
        std::cerr<<"ERROR: variable is not float type"<<std::endl;
}
void Variable::set (char value) {
    if (type==CHAR)
        this->val = value;
    else
        std::cerr<<"ERROR: variable is not char type"<<std::endl;
}

std::string Variable::toStr() {
    if(type == STRING)
        return val;
    std::cerr<<"Error: variable is not string type"<<std::endl;
    return "";
}
int Variable::toInt() {
    if(type == INT)
        return std::stoi(val);
    std::cerr<<"Error: variable is not int type"<<std::endl;
    return 0;
}
float Variable::toFloat() {
    if(type == FLOAT)
        return std::stof(val);
    std::cerr<<"Error: variable is not float type"<<std::endl;
    return 0;
}

char Variable::toChar() {
    if(type == CHAR)
        return (val.front());
    std::cerr<<"Error: variable is not char type"<<std::endl;
    return 0;
}

    //// dtor ////
Variable::~Variable ()
{
}

}} // namespaces
