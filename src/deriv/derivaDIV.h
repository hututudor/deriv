
#ifndef DERIVADIV_H
#define DERIVADIV_H

#include "global.h"

void DerivaDIV(node_t*& start);
void createPowPatrat(node_t* start, node_t*& powPatrat);
void createFMULGderivat(node_t* start, node_t*& secondMultiplication);
void createFderivatMULG(node_t* start, node_t*& firstMultiplication);

#endif