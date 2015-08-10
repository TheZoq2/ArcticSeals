#include "editor.h"

int main()
{
    Editor editor;
    
    editor.setup();

    while(editor.isDone() == false)
    {
        editor.loop();
    }
    editor.cleanup();

    return 0;
}
