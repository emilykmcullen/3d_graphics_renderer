
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
    for (int y = centreY - radius - thickness; y <= centreY + radius + thickness; y++)
    {
        for (int x = centreX - radius - thickness; x <= centreX + radius + thickness; x++)
        {
            //Calculate distance between current x,y point and centre point
            int x2 = (x - centreX)*(x - centreX);
            int y2 = (y - centreY)*(y - centreY);
            int distance = sqrt(x2 + y2);
            //If distance is close to radius, draw point
            if (distance <= (radius + thickness) && distance >= (radius - thickness))
            {
                color_buffer[(window_width * y) + x] = color;
            }
        }
    }
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