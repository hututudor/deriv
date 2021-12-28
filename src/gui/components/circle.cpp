#include "circle.h"

#include "../arrays/circle_array.h"
#include "../utils/context.h"

void add_circle(void* context, circle_t circle) {
  context_t* ctx = (context_t*)context;

  push_circle_array(ctx->circle_array, circle);
}

void add_circle(void* context, vector_t center_pos, int radius,
                color_t background, color_t border_color) {
  circle_t circle;

  circle.center_pos = center_pos;
  circle.radius = radius;

  circle.background = background;
  circle.border_color = border_color;

  return add_circle(context, circle);
}

void render_circle(void* context, circle_t circle) {
  context_t* ctx = (context_t*)context;

  SDL_RenderFillCircle(ctx->renderer, circle.center_pos, circle.radius,
                       circle.background);
  SDL_RenderDrawCircle(ctx->renderer, circle.center_pos, circle.radius,
                       circle.border_color);
}

void SDL_RenderDrawCircle(SDL_Renderer* renderer, vector_t center_pos,
                          int radius, color_t border_color) {
  int offsetx, offsety, d;

  offsetx = 0;
  offsety = radius;
  d = radius - 1;

  SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g,
                         border_color.b, border_color.a);

  while (offsety >= offsetx) {
    SDL_RenderDrawPoint(renderer, center_pos.x + offsetx,
                        center_pos.y + offsety);
    SDL_RenderDrawPoint(renderer, center_pos.x + offsety,
                        center_pos.y + offsetx);
    SDL_RenderDrawPoint(renderer, center_pos.x - offsetx,
                        center_pos.y + offsety);
    SDL_RenderDrawPoint(renderer, center_pos.x - offsety,
                        center_pos.y + offsetx);
    SDL_RenderDrawPoint(renderer, center_pos.x + offsetx,
                        center_pos.y - offsety);
    SDL_RenderDrawPoint(renderer, center_pos.x + offsety,
                        center_pos.y - offsetx);
    SDL_RenderDrawPoint(renderer, center_pos.x - offsetx,
                        center_pos.y - offsety);
    SDL_RenderDrawPoint(renderer, center_pos.x - offsety,
                        center_pos.y - offsetx);

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }
}

void SDL_RenderFillCircle(SDL_Renderer* renderer, vector_t center_pos,
                          int radius, color_t background) {
  int offsetx, offsety, d;

  offsetx = 0;
  offsety = radius;
  d = radius - 1;

  SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b,
                         background.a);
  while (offsety >= offsetx) {
    SDL_RenderDrawLine(renderer, center_pos.x - offsety, center_pos.y + offsetx,
                       center_pos.x + offsety, center_pos.y + offsetx);
    SDL_RenderDrawLine(renderer, center_pos.x - offsetx, center_pos.y + offsety,
                       center_pos.x + offsetx, center_pos.y + offsety);
    SDL_RenderDrawLine(renderer, center_pos.x - offsetx, center_pos.y - offsety,
                       center_pos.x + offsetx, center_pos.y - offsety);
    SDL_RenderDrawLine(renderer, center_pos.x - offsety, center_pos.y - offsetx,
                       center_pos.x + offsety, center_pos.y - offsetx);

    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if (d < 2 * (radius - offsety)) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }
}