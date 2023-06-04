
#include "Verticle.h"
#include "Node.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Service.h"
#include <limits.h>



Node* new_node()
    {
    return (Node*)calloc(1,sizeof(Node));
    }

void construct_node(Node* to_build)
    {
    to_build->visit_tag = 0;
    to_build->shortest_way_to = INT_MAX;
    to_build->connected_verticles = calloc(1,sizeof(to_build->connected_verticles));
    to_build->connected_nodes = calloc(1,sizeof(to_build->connected_nodes));
    to_build->num_con_vert = 0;
    to_build->node_id = NULL;
    }


void create_verticle(Node* f_node,Node* s_node,int weight)
    {
    if(weight == INT_MAX || weight == INT_MIN)
        {
        printf("You can't create verticle this lenght!\n");
        return;
        }
    Verticle* n_vert = new_verticle();
    n_vert->weight = weight;
    if (f_node != s_node)
        {
        add_verticle(n_vert,f_node,s_node);
        add_verticle(n_vert,s_node,f_node);
        }
    else
        {
        add_verticle(n_vert,f_node,s_node);
        }
    }

void add_verticle(Verticle* n_vert,Node* cur_node,Node* to_connect)
    {
    cur_node->num_con_vert++;
    cur_node->connected_verticles = (Verticle**)realloc(cur_node->connected_verticles,cur_node->num_con_vert*sizeof(Verticle*));
    cur_node->connected_nodes = (Node**)realloc(cur_node->connected_nodes,cur_node->num_con_vert*sizeof(Node*));
    cur_node->connected_verticles[cur_node->num_con_vert - 1] = n_vert;
    cur_node->connected_nodes[cur_node->num_con_vert - 1] = to_connect;
    }

Verticle* get_verticle(Node* f_node,Node* s_node)
    {
    if(f_node != s_node)
        {
        for(int i = 0; i < f_node->num_con_vert; i++)
            {
            Verticle* search = f_node->connected_verticles[i];
            for (int j = 0; j < s_node->num_con_vert;j++)
                {
                if (search == s_node->connected_verticles[j])
                    {
                    return search;
                    }
                }
            }
        }
    else
        {
        for (int i = 0; i < f_node->num_con_vert; i++)
            {
            if(f_node->connected_nodes[i] == f_node)
                {
                return f_node->connected_verticles[i];
                }
            }
        }
    return NULL;
    }

Verticle* get_shortest_verticle(Node* node)
    {
    int min = INT_MAX;
    Verticle* shortest_verticle = NULL;
    for(int i = 0; i < node->num_con_vert; i++)
        {
        if(node->connected_verticles[i]->weight < min)
            {
            min = node->connected_verticles[i]->weight;
            shortest_verticle = node->connected_verticles[i];
            }
        }
    return shortest_verticle;
    }

Node* get_closest_unvisited_node(Node* node)
    {
    Node* closest_unvisited_node = NULL;
    int min = INT_MAX;
    for(int i = 0; i < node->num_con_vert; i++)
        {
        if(node->connected_verticles[i]->weight < min && node->connected_nodes[i]->visit_tag != 1)
            {
            min = node->connected_verticles[i]->weight;
            closest_unvisited_node = node->connected_nodes[i];
            }
        }
    return closest_unvisited_node;
    }


void remove_verticle(Verticle* to_delete,Node* cur_node)
    {
    int i_to_del = -1;
    for(int i = 0; i < cur_node->num_con_vert; i++)
        {
        if (cur_node->connected_verticles[i] == to_delete)
            {
            i_to_del = i;
            }
        }
    
    if (i_to_del >= 0 && i_to_del < cur_node->num_con_vert - 1)
        {
        for (int i = i_to_del; i < cur_node->num_con_vert -1;i++)
            {
            cur_node->connected_verticles[i] = cur_node->connected_verticles[i+1];
            cur_node->connected_nodes[i] = cur_node->connected_nodes[i+1];
            }
        cur_node->num_con_vert--;
        cur_node->connected_verticles = (Verticle**)realloc(cur_node->connected_verticles,cur_node->num_con_vert*sizeof(Verticle*));
        cur_node->connected_nodes = (Node**)realloc(cur_node->connected_nodes,cur_node->num_con_vert*sizeof(Node*));
        }
    else if(i_to_del >= 0 && i_to_del == cur_node->num_con_vert - 1)
        {
        cur_node->num_con_vert--;
        cur_node->connected_verticles = (Verticle**)realloc(cur_node->connected_verticles,cur_node->num_con_vert*sizeof(Verticle*));
        cur_node->connected_nodes = (Node**)realloc(cur_node->connected_nodes,cur_node->num_con_vert*sizeof(Node*));
        }
    }

void delete_verticle(Node* f_node,Node* s_node)
    {
    Verticle* to_delete = get_verticle(f_node,s_node);
    remove_verticle(to_delete,f_node);
    remove_verticle(to_delete,s_node);
    free(to_delete);
    }

void delete_node(Node* to_delete)
    {
    while (to_delete->num_con_vert != 0)
        {
        if(to_delete,to_delete->connected_nodes[0] != NULL)
            {
            delete_verticle(to_delete,to_delete->connected_nodes[0]);
            }
        }
    free(to_delete->connected_verticles);
    free(to_delete->connected_nodes);
    free(to_delete->node_id);
    free(to_delete);
    }