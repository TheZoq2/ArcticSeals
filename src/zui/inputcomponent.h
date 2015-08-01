#ifndef H_INPUTCOMPONENT
#define H_INPUTCOMPONENT

#include "inputcomponent.h"

#include <string>
#include <vector>

class InputComponent;

class InputListener
{
public:
    void onInputChange(InputComponent* changedComponent);
};

class InputComponent
{
public:
    bool boolValue();
    int intValue();
    float floatValue();
    std::stirng stringValue();

private:
    std::string name;
    
    std::vector<InputListener*> listeners;
};
#endif
