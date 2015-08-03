#ifndef H_INPUTCOMPONENT
#define H_INPUTCOMPONENT

#include <string>
#include <vector>

#include "../vec2f.h"

namespace zui
{
    class InputComponent
    {
    public:
        InputComponent(std::string name);

        virtual bool boolValue() = 0;
        virtual int intValue() = 0;
        virtual float floatValue() = 0;
        virtual std::string stringValue() = 0;

        std::string getName();
    private:
        std::string name;
    
        bool valueChanged;
    };
};
#endif
