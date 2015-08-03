#ifndef H_BUTTON
#define H_BUTTON

#include "uicomponent.h"
#include "inputcomponent.h"
#include "../vec2f.h"

namespace zui
{
    class Button : public UIComponent, public InputComponent
    {
    public:
        Button(Vec2f pos, std::string name);
        
        bool boolValue();
        int intValue();
        float floatValue();
        std::string stringValue();
    protected:
        enum State
        {
            OFF,
            CLICKED,
            PRESSED,
            HOVERED
        };

        State state;
    private:
    };
};
#endif
