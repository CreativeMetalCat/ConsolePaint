// ConsolePaint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Brush.h"

//i don't know why, but unless expicitly stated here linker just ignored the library
#pragma comment(lib,"./pdcurses/pdcurses")


struct MouseInfo
{
    bool button1 = true;

    //location on the last update
    Vector PreviousLocation;

    MouseInfo() {}
};

struct Program 
{
    Canvas* Canvas = nullptr;
    Brush* Brush = nullptr;
    bool working = true;
    MouseInfo mouseInfo;

    Program(){}
};

int main()
{
    WINDOW* window = initscr();
    mvaddch(9, 9, 'a');

    //pdcurses setup
    keypad(window, true);
    noecho();
    raw();

    // Makes the terminal report mouse movement events
    printf("\033[?1003h\n");

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);

    //program setup
    Program prog;
    prog.Canvas = new Canvas({ 100,100 });
    prog.Brush = new Brush();
    
    while (prog.working)
    {
        int input = getch(window);
        switch (input)
        {
        case KEY_MOUSE:
            MEVENT mouseEvent;
            if (nc_getmouse(&mouseEvent) == OK)
            {
                Vector mouseLoc = Vector{ mouseEvent.x, mouseEvent.y };
                if (mouseEvent.bstate & BUTTON1_PRESSED)
                {
                    prog.mouseInfo.button1 = true;
                    mvaddch(mouseEvent.y, mouseEvent.x, 'a');
                    prog.Brush->Apply(prog.Canvas, Vector{mouseEvent.x ,mouseEvent.y });
                    prog.mouseInfo.PreviousLocation = Vector{ mouseEvent.x ,mouseEvent.y };
                    //catch mouse press start
                }
                if (mouseEvent.bstate & BUTTON1_RELEASED)
                {
                    prog.mouseInfo.button1 = false;
                    mvaddch(mouseEvent.y, mouseEvent.x, 'a');
                    //catch mouse press end
                }
                if (prog.mouseInfo.button1)
                {
                    //get difference beetween locations
                    //and draw line beetween them

                    
                    Vector diff = mouseLoc - prog.mouseInfo.PreviousLocation;
                    if (diff != Vector{ 0,0 })
                    {
                        prog.Canvas->Line(prog.mouseInfo.PreviousLocation, mouseLoc, 'a');
                    }
                    mvaddch(mouseEvent.y, mouseEvent.x, 'a');

                    prog.mouseInfo.PreviousLocation = mouseLoc;
                }
                
            }
            break;
        default:
            break;
        }
    }
    endwin();
}
