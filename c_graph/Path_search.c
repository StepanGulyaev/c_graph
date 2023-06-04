#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Verticle.h"
#include "Node.h"
#include "Node_array.h"
#include "Path_search.h"
#include "Service.h"
#include <limits.h>

void search_path(Node* from,Node* to)
    {
    Node_array* visited = new_node_array();
    construct_node_array(visited);
    search_in_depth(from,to,visited);
    if (visited->size == 0)
        {
        printf("\n");
        printf("There is no way between these nodes!\n");
        printf("\n");
        }
    else
        {
        printf("\n");
        printf("Way: ");
        printf("%s",visited->node_arr[0]->node_id);
        for(int i = 1; i < visited->size; i++)
            {
            printf("-%s",visited->node_arr[i]->node_id);
            }
        printf(" Length: ");
        printf("%d",get_way_length(visited));
        printf("\n");
        printf("\n");
        }
    free(visited->node_arr);
    free(visited);
    }

void search_in_depth(Node* from,Node* to,Node_array* visited)
    {
    from->visit_tag = 1;
    push_to_array(from,visited);
    if(to->visit_tag == 1)
        {
        return;
        }
    else 
        {
        for(int i = 0; i < from->num_con_vert;i++)
            {
            if(from->connected_nodes[i]->visit_tag == 0)
                {
                search_in_depth(from->connected_nodes[i],to,visited);
                if(to->visit_tag == 1)
                    {
                    break;
                    }
                }
            }
        if(to->visit_tag != 1)
            {
            remove_node_from_array(from,visited);
            }
        }
    }

void search_shortest_path(Node* from,Node* to,Node_array* array)
    {
    int result = 0;
    from->shortest_way_to = 0;
    if(is_negaitve_verticles(array))
        {
        Node_array* copy = new_node_array();
        construct_node_array(copy);
        copy_with_new_nodes(copy, array);

        Node* from_copy = get_address_by_name(from->node_id, copy);
        Node* to_copy = get_address_by_name(to->node_id, copy);
        bellman_ford_algorithm(from_copy,to_copy,copy,&result);
        delete_node_array(copy);
        }
    else
        {
        dijkstra_algorithm(from,to,&result);
        }
    printf("\n");
    if (result == INT_MAX)
        {
        printf("There is no way between these nodes!\n");
        }
    else 
        {
        printf("Shortest path between %s and %s has length: %d\n",from->node_id,to->node_id,result);
        }
    printf("\n");
    }

void dijkstra_algorithm(Node* from,Node* to,int* result)
    {
    for(int i = 0; i < from->num_con_vert; i++)
        {
        if((from->shortest_way_to + from->connected_verticles[i]->weight < from->connected_nodes[i]->shortest_way_to)&&(from->visit_tag!=1))
            {
            from->connected_nodes[i]->shortest_way_to = from->shortest_way_to + from->connected_verticles[i]->weight;
            }
        }
    Node* closest_node = get_closest_unvisited_node(from);
    if(closest_node != NULL)
        {
        from->visit_tag = 1;
        dijkstra_algorithm(closest_node,to,result);
        }
    *(result) = to->shortest_way_to;
    return;
    }

void bellman_ford_algorithm(Node* from,Node* to,Node_array* array,int* result)
    {
    for(int i = 0; i < array->size - 1;i++)
        {
        Node_array* tmp = new_node_array();
        construct_node_array(tmp);
        copy_with_new_nodes(tmp,array);
        for(int j = 0; j < tmp->size;j++)
            {
            Node* cur_node_in_copy = tmp->node_arr[j];
            Node_array* desc_ways = new_node_array();
            construct_node_array(desc_ways);
            desc_way(desc_ways,cur_node_in_copy);
            for(int k = 0; k < desc_ways->size;k++)
                {
                char* name = desc_ways->node_arr[k]->node_id;
                Node* node_to_change_short_way = get_address_by_name(name,array);
                node_to_change_short_way->shortest_way_to = desc_ways->node_arr[k]->shortest_way_to;
                delete_verticle(cur_node_in_copy,desc_ways->node_arr[k]);
                }
            free(desc_ways->node_arr);
            free(desc_ways);
            }
        delete_node_array(tmp);
        }
    *(result) = to->shortest_way_to;
    }

void components(Node_array* array)
    {
    Node_array* copy = new_node_array();
    construct_node_array(copy);
    copy_node_array(copy,array);
    printf("Components: \n");
    while(copy->size != 0)
        {
        printf("\n");
        Node_array* component = new_node_array();
        construct_node_array(component);

        push_to_array(copy->node_arr[0],component);
        for(int i = 0; i < copy->node_arr[0]->num_con_vert;i++)
            {
            push_to_array(copy->node_arr[0]->connected_nodes[i],component);
            remove_node_from_array(copy->node_arr[0]->connected_nodes[i],copy);
            }
        for(int i = 1; i < copy->size;i++)
            {
            Node_array* visited = new_node_array();
            construct_node_array(visited);
            search_in_depth(copy->node_arr[0],copy->node_arr[i],visited);
            if (visited->size != 0)
                {
                push_to_array(copy->node_arr[i],component);
                remove_node_from_array(copy->node_arr[i],copy);
                }
            free(visited->node_arr);
            free(visited);
            }
        remove_node_from_array(copy->node_arr[0],copy);
        printf("        ");
        print_node_array(component);
        printf("\n");
        free(component->node_arr);
        free(component);
        }
    free(copy->node_arr);
    free(copy);
    printf("\n");
    }