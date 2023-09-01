#define OLC_PGE_APPLICATION
#include "Graphics.h"
#include "LR35902.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;




// void render_axis(){
//     //horizontal axis y
//     SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255);
//     SDL_RenderDrawLine(app.renderer, WINDOW_W * 0.5, WINDOW_H * 0.80, WINDOW_W * 0.5, WINDOW_H * 0.80-500);


//     //vertical axis x
//     SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
//     SDL_RenderDrawLine(app.renderer, WINDOW_W * 0.20, WINDOW_H * 0.5, WINDOW_W * 0.2+800, WINDOW_H * 0.5);

// }

/*
3C
00
42
00
B9
00
A5
00
B9
00
A5
00
42
00
3C
00
*/


//now testing ADC8
int main() {



    Processor *proc = new Processor();
    

    proc->load_rom("tetris.gb");
    proc->load_boot_routine();
    proc->initialization();

    Gameboy* game = new Gameboy(*proc);
    if (game->Construct(160 * 5, 144 * 5, 1, 1))
        game->Start();


    getchar();
    return 0;
}