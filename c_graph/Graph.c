#include "Verticle.h"
#include "Node.h"
#include "List.h"
#include "Graph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Service.h"


Graph* new_graph()
    {
    return (Graph*)calloc(1,sizeof(Graph));
    }

void construct_graph(Graph* to_construct)
    {
    to_construct->num_of_nodes = 0;    
    to_construct->nodes =  calloc(1,sizeof(to_construct->nodes));
    }

void push_list(Graph* graph,List* list)
    {
    graph->num_of_nodes++;
    graph->nodes = (List**)realloc(graph->nodes,graph->num_of_nodes*sizeof(List*));
    graph->nodes[graph->num_of_nodes-1] = list;
    }

void build_graph(Graph* to_build, Node_array* array)
    {
    for(int i = 0; i < array->size; i++)
        {
        List* list = new_list();
        construct_list(list);
        build_list(list,array->node_arr[i]);
        push_list(to_build,list);
        }
    }

void print_graph(Graph* to_print)
    {
    for(int i = 0; i < to_print->num_of_nodes; i++)
        {
        print_list(to_print->nodes[i]);
        printf("\n");
        }
    }

void delete_graph(Graph* to_delete)
    {
    for(int i = 0; i < to_delete->num_of_nodes;i++)
        {
        delete_list(to_delete->nodes[i]);
        }
    free(to_delete->nodes);
    free(to_delete);
    }