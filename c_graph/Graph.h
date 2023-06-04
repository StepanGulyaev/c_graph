#ifndef GRAPH_H
#define GRAPH_H
#include "Verticle.h"
#include "Node.h"
#include "List.h"

typedef struct Graph
    {
    unsigned int num_of_nodes;
    List** nodes;
    }Graph;

Graph* new_graph();
void construct_graph(Graph*);
void push_list(Graph*,List*);
void build_graph(Graph*,Node_array*);
void print_graph(Graph*);
void delete_graph(Graph*);

#endif