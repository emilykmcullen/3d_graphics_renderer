#include <stdio.h>
#include <stdint.h> 
#include <SDL2/SDL.h>
#include "display.h"
#include <SDL2/SDL_image.h>

bool is_running = false;

void setup(void)
{
    //Allocate the required memory in bytes for the buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    if (!color_buffer)
    {
        //todo
    }
    else
    {
        //todo
    }
    //Set up the texture
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
    if (!color_buffer_texture)
    {
        //todo
    }
    else
    {
        //todo
    }

}

void render(void)
{
    //Set the color used for drawing operations (Rect, Line and Clear).
    SDL_SetRenderDrawColor(renderer, 255, 0, 0 , 255);

    //Clear the current rendering target with the drawing color (we are drawing to backbuffer here)
    SDL_RenderClear(renderer);

    //Copies color buffer to texture
    //Copies texture to renderer
    //(Still drawing to backbuffer here)
    render_color_buffer();
    
    
    //This just fills our local colour buffer array with whatever colour we pass, there is no SDL call
    clear_color_buffer(0xFFFFFF00);
    
    //Update the screen with any rendering performed since the previous call. (Backbuffer we have been drawing to is swapped to frontbuffer)
    SDL_RenderPresent(renderer);
}

void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
    }
}

void update(void)
{

}



int main()
{
    is_running = initialize_window();

    setup();

    while(is_running)
    {
        process_input();
        update();
        render();
    }
    
    destroy_window();

    return 0;
}