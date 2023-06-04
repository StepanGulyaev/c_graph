#include "Verticle.h"
#include "Node.h"
#include "List.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Service.h"


List_node* new_list_node()
    {
    return (List_node*)calloc(1,sizeof(List_node));
    }

void construct_list_node(List_node* to_build,Node* to_put_node,Verticle* to_put_verticle)
    {
    to_build->cur_node = to_put_node;
    to_build->vert_to_first = to_put_verticle;
    to_build->next = NULL;
    }

void construct_list_first_node(List_node* to_build,Node* to_put_node)
    {
    to_build->cur_node = to_put_node;
    to_build->vert_to_first = NULL;
    to_build->next = NULL;
    }

void print_list_node(List_node* to_print)
    {
    printf("-> %s %d ",to_print->cur_node->node_id,to_print->vert_to_first->weight);
    }

void delete_list_node(List_node* to_delete)
    {
    free(to_delete);
    }

List* new_list()
    {
    return (List*)calloc(1,sizeof(List));
    }

void construct_list(List* to_build)
    {
    to_build->head = NULL;
    to_build->length = 0;
    }

void push_to_list(List* list,List_node* to_push)
    {
    if (list->head == NULL)
        {
        list->head = to_push;
        }
    else
        {
        List_node* tmp = list->head;
        List_node* traceback = tmp;
        while (tmp != NULL)
            {
            traceback = tmp;
            tmp = tmp->next;
            }
        traceback->next = to_push;
        }
    list->length++;
    }

void build_list(List* to_build,Node* node)
    {
    List_node* first_node = new_list_node();
    construct_list_first_node(first_node,node);
    push_to_list(to_build,first_node);

    for(int i = 0; i < node->num_con_vert; i++)
        {
        List_node* list_node = new_list_node();
        construct_list_node(list_node,node->connected_nodes[i],node->connected_verticles[i]);
        push_to_list(to_build,list_node);
        }
    }

void print_list(List* to_print)
    {
    printf("%s ",to_print->head->cur_node->node_id);
    List_node* tmp = to_print->head->next;
    while (tmp!=NULL)
        {
        print_list_node(tmp);
        tmp = tmp->next;
        }
    }

void delete_list(List* list)
    {
    List_node* tmp = list->head;
    List_node* next = tmp;
    while(tmp != NULL)
        {
        next = tmp->next;
        delete_list_node(tmp);
        tmp = next;
        }
    free(list);
    }

