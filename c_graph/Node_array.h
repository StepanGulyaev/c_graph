#ifndef NODE_ARR_H
#define NODE_ARR_H
#include "Verticle.h"
#include "Node.h"

typedef struct Node_array
    {
    Node** node_arr;
    unsigned int size;
    }Node_array;

Node_array* new_node_array();
void construct_node_array(Node_array*);
int name_unique(char*,Node_array*);
int node_exist(char*,Node_array*);
void add_node_info(Node*,Node_array*);
void push_to_array(Node*,Node_array*);
void add_node_to_array(Node_array*);
void add_verticle_to_array(Node_array*);
int get_way_length(Node_array*);
void build_node_array(Node_array*);
Node* get_address_by_name(char*,Node_array*);
void print_node_array(Node_array*);
void tags_set_default(Node_array*);
void shortest_ways_set_default(Node_array*);
int is_negaitve_verticles(Node_array*);
void remove_node_from_array(Node*,Node_array*);
void delete_node_from_array(Node*,Node_array*);
void copy_node_array(Node_array*,Node_array*);
void copy_with_new_nodes(Node_array*,Node_array*);
void desc_way(Node_array*,Node*);
void delete_node_array(Node_array*);

#endif
