#ifndef LIST_H
#define LIST_H
#include "Verticle.h"
#include "Node.h"
#include "Node_array.h"

typedef struct List_node
    {
    Node* cur_node;
    Verticle* vert_to_first;
    struct List_node* next;
    }List_node;

typedef struct List
    {
    List_node* head;
    unsigned int length;
    }List;

List_node* new_list_node();
void construct_list_first_node(List_node*,Node*);
void construct_list_node(List_node*,Node*,Verticle*);
void print_list_node(List_node*);
void delete_list_node(List_node*);

List* new_list();
void construct_list(List*);
void push_to_list(List*,List_node*);
void build_list(List*,Node*);
void print_list(List*);
void delete_list(List*);

#endif