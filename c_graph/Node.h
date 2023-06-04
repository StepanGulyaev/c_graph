#ifndef NODE_H
#define NODE_H
#include "Verticle.h"

typedef struct Node
    {
    Verticle** connected_verticles;
    unsigned int num_con_vert;
    struct Node** connected_nodes;
    int visit_tag;
    int shortest_way_to;
    char* node_id;
    }Node;

Node* new_node();
void construct_node(Node*);
void create_verticle(Node*,Node*,int);
Verticle* get_verticle(Node*,Node*);
Verticle* get_shortest_verticle(Node*);
Node* get_closest_unvisited_node(Node*);  
void add_verticle(Verticle*,Node*,Node*);
void remove_verticle(Verticle*,Node*);
void delete_verticle(Node*,Node*);
void delete_node(Node*);

#endif