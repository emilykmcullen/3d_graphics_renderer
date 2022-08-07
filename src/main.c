#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> 
#include <SDL2/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;
bool is_running;
int window_width = 800;
int window_height = 600;

//Declare a pointer to an array of uint32 elements
uint32_t* color_buffer = NULL;

SDL_Texture* color_buffer_texture = NULL;


//in c if I leave the arguments empty, you can enter any number of arguments
bool initialize_window(void)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    //Create SDL Window
    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    //Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer\n");
        return false;
    }

    return true;
}

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
            break;
    }
}

void update(void)
{

}

void render_color_buffer(void)
{
    //final param is the width of our row
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color)
{
    for (int i = 0; i < (window_width * window_height); i++)
    {
        color_buffer[i] = color;
    }

    // for (int y = 0; y < window_height; y++)
    // {
    //     for (int x = 0; x < window_width; x++)
    //     {
    //         color_buffer[(window_width * y) + x] = color;
    //     }
    // }
}

void draw_grid(uint32_t color, int rowSize, int columnSize)
{
    for (int y = 0; y < window_height; y++)
    {
        if (y % rowSize == 0)
        {
            for (int x = 0; x < window_width; x++)
            {
                color_buffer[(window_width * y) + x] = color;
            }
        }
        else
        {
            for (int x = 0; x < window_width; x += columnSize)
            {
                color_buffer[(window_width * y) + x] = color;
            }
        }    
    }

    // when y = 0, 60, 120, 180, 240, 300, 360, 420, 480, 540, 600, colour the whole x row
    //otherwise color just x = 0, 80, etc.
}

void draw_square(uint32_t color, int originX, int originY, int sideLength)
{
    if (originX + sideLength > window_width || originY + sideLength > window_height)
    {
        printf("Square out of bounds of window\n");
        return;
    }
    //start at origin and fill in the row until x = x + sideLength
    // fill in the column until y = y + sidelength
    // fille in the row at y + sidelength until x = x + sidelength
    // fill in the column at x + sidelength until y = y + sidelength

    for (int y = originY; y <= originY + sideLength; y++)
    {
        //draw top and bottom row of the square
        if (y == originY || y == originY + sideLength)
        {
            for (int x = originX; x < originX + sideLength; x++)
            {
                color_buffer[(window_width * y) + x] = color;
            }
        }

        //draw columns
        else
        {
            //draw x = originX and x = originX + sideLength
            color_buffer[(window_width * y) + originX] = color;
            color_buffer[(window_width * y) + originX + sideLength] = color;
        }
        
    }
}

void draw_solid_square(uint32_t color, int originX, int originY, int sideLength)
{
    if (originX + sideLength > window_width || originY + sideLength > window_height)
    {
        printf("Solid square out of bounds of window\n");
        return;
    }
    //for each y, colour every x from x to x + sidelength
    for (int y = originY; y < originY + sideLength; y++)
    {
        for (int x = originX; x < originX + sideLength; x++)
        {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void draw_circle(uint32_t color, int centreX, int centreY, int radius, int thickness)
{
    //centre a, b
    //( x − a )^2 + ( y − b )^2 = r^2



    //check the radius between my centre point and the point, if it is equal to radius, draw the cirlce
    //I don't need to check all points in the window, I can check all points between:
    // x >= centreX - radius and x <= centreX + radius
    // y >= centreY - raidus and y <= centreY + radius

    for (int y = centreY - radius - thickness; y <= centreY + radius + thickness; y++)
    {
        for (int x = centreX - radius - thickness; x <= centreX + radius + thickness; x++)
        {
            // if distance is less than radius + 3 and more than raidus - 3 
            //eg. if raidus is 10:
            // draw point if distance is less than 13 and more than 7
            int x2 = (x - centreX)*(x - centreX);
            int y2 = (y - centreY)*(y - centreY);
            int distance = sqrt(x2 + y2);
            if (distance <= (radius + thickness) && distance >= (radius - thickness))
            {
                color_buffer[(window_width * y) + x] = color;
            }
        }
    }


}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0 , 255);
    SDL_RenderClear(renderer);

    clear_color_buffer(0xFFFFFF00);
    draw_grid(0xFF00FF00, 5, 40);

    //draw_square(0xFF0000FF, 100, 150, 100);
    //draw_solid_square(0xFF0000FF, 300, 300, 100);
    draw_circle(0xFF0000FF, 400, 450, 50, 5);


    render_color_buffer();

    SDL_RenderPresent(renderer);
}

void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void)
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