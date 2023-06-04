#ifndef PATH_SEARCH_H
#define PATH_SEARCH_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Verticle.h"
#include "Node.h"
#include "Node_array.h"

void search_path(Node*,Node*);
void search_in_depth(Node*,Node*,Node_array*);
void search_shortest_path(Node*,Node*,Node_array*);
void dijkstra_algorithm(Node*,Node*,int*);
void bellman_ford_algorithm(Node*,Node*,Node_array*,int*);
void components(Node_array*);

#endif