#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h> 

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int window_width;
extern int window_height;
//Declare a pointer to an array of uint32 elements
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

bool initialize_window(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);


#endif