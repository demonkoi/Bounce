#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>

void Circle(int center_x, int center_y, int radius, SDL_Color color, SDL_Window* window);

#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 880

int main(int argc, char* args[])
{
    // The window we'll be rendering to
    SDL_Window* window = NULL;
    
    // The surface contained by the window
    
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("Bounce", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return 1;
        }
        else
        {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

            // Update the surface
            SDL_UpdateWindowSurface(window);
            // Wait two secondso
            int x,y,radius,xvel,yvel;
            x = SCREEN_WIDTH/2;
            y = SCREEN_HEIGHT/2;
            xvel =5;
            yvel =12;
            radius = 20;
            SDL_Color color;
            
            while (true) {
              int s = rand()%7 - 3;
              radius += s;
              if (radius < 5) {
                  radius = 5;
              }

            if (x+radius>=SCREEN_WIDTH-10 || x-radius<=0) {
                int r = (rand()%10) - 5;
                yvel += r;
                xvel = -xvel;
            }
            if (y+radius>=SCREEN_HEIGHT-10 || y-radius<=0) {
                int r = (rand()%10) - 5;
                xvel += r;
                yvel = -yvel;
            }
            color.r = rand()%255;
            color.g = rand()%255;
            color.b = rand()%255;
        

            x+=xvel;
            y+=yvel;
            Circle(x,y,radius,color,window);
            SDL_Delay(33);

            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
void Circle(int center_x, int center_y, int radius, SDL_Color color, SDL_Window* window) {
  SDL_Surface* windowSurface = SDL_GetWindowSurface(window); // Declare and initialize windowSurface
  if (windowSurface == NULL) {
    printf("Window surface could not be retrieved! SDL_Error: %s\n", SDL_GetError());
    return;
  }
  uint32_t *pixels = (uint32_t *) windowSurface->pixels;
  SDL_PixelFormat *windowFormat = windowSurface->format;
  if (SDL_LockSurface(windowSurface) < 0) {
    printf("Surface could not be locked! SDL_Error: %s\n", SDL_GetError());
    return;
  }

  int WIDTH = windowSurface->w; // Define the value of WIDTH
  int radiussqrd = radius * radius;

  for(int x=center_x-radius; x<=center_x+radius; x++) {
    int dx = center_x - x;
    for(int y=center_y-radius; y<=center_y+radius; y++) {
      int dy = center_y - y;
      if((dy * dy + dx * dx) <= radiussqrd) {
        pixels[(y * WIDTH + x)] = SDL_MapRGB(windowFormat, color.r, color.g, color.b);
      }
    }
  }

  SDL_UnlockSurface(windowSurface);
  SDL_UpdateWindowSurface(window);
}

