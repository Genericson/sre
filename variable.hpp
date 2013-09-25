#ifndef SRE_VARIABLE_HPP
#define SRE_VARIABLE_HPP

#include <memory>

namespace sre { namespace console {

class Variable
{
public:
    enum TYPE {
        STRING,
        INT,
        FLOAT,
        CHAR
    };
private:
    std::string name;
    Variable::TYPE type;
    std::string val;

public:
        Variable (std::string name, Variable::TYPE type, std::string val);
        std::string toString();

        void set (std::string value);
        void set (int value);
        void set (float value);
        void set (char value);

        std::string getName ()  {return name;}
        std::string getVal ()   {return val;}
        Variable::TYPE getType () {return type;}

        std::string toStr();
        int toInt();
        float toFloat();
        char toChar();

        ~Variable ();
};

}} // namespaces

#endif // SRE_VARIABLE_HPP
