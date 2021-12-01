// ConsolePaint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Brush.h"

//i don't know why, but unless expicitly stated here linker just ignored the library
#pragma comment(lib,"./pdcurses/pdcurses")

struct Program 
{
    Canvas* Canvas = nullptr;
    Brush* Brush = nullptr;
    bool working = true;
    bool button1 = true;
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
    Program prog = Program();
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
                if (mouseEvent.bstate & BUTTON1_PRESSED)
                {
                    prog.button1 = true;
                    mvaddch(mouseEvent.y, mouseEvent.x, 'a');
                    prog.Brush->Apply(prog.Canvas, Vector{mouseEvent.x ,mouseEvent.y });
                    //catch mouse press start
                }
                if (mouseEvent.bstate & BUTTON1_RELEASED)
                {
                    prog.button1 = false;
                    mvaddch(mouseEvent.y, mouseEvent.x, 'a');
                    //catch mouse press end
                }
                if (prog.button1)
                {
                    mvaddch(mouseEvent.y, mouseEvent.x, 'a');
                }
                
            }
            break;
        default:
            break;
        }
    }
    endwin();
}
