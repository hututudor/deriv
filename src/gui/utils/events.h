#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>

void handle_key_press(void* context, SDL_Keysym sym);
void handle_mouse_move(void* context, SDL_MouseMotionEvent event);

#endif