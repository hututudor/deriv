#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "../utils/context.h"

void add_sidebar(context_t* context);
void update_sidebar(context_t* context);
void render_sidebar(context_t* context);
void destroy_sidebar(context_t* context);

#endif