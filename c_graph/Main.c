#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Verticle.h"
#include "Node.h"
#include "Node_array.h"
#include "List.h"
#include "Graph.h"
#include "Path_search.h"
#include "Service.h"


void print_adjacency_list(Node_array* array)
    {
    Graph* graph = new_graph();
    construct_graph(graph);
    build_graph(graph,array);
    printf("\n");
    print_graph(graph);
    printf("\n");
    delete_graph(graph);
    }

void run_menu()
    {
    Node_array* array = new_node_array();
    construct_node_array(array);
    int empty_graph = 1;
    while (1)
        {
        printf("Graph builder menu\n");
        printf("  Press 1 to create graph\n");
        printf("  Press 2 to add node\n");
        printf("  Press 3 to add verticle\n");
        printf("  Press 4 to delete node\n");
        printf("  Press 5 to delete verticle\n");
        printf("  Press 6 to search path between two nodes\n");
        printf("  Press 7 to search shortest path between two nodes\n");
        printf("  Press 8 to see connected components\n");
        printf("  Press 9 to delete graph\n");
        printf("  Press 0 to exit\n");

        printf("Enter option: ");
        char* option = read_string(100);

        if(!strcmp(option,"1"))
            {
            build_node_array(array);
            print_adjacency_list(array);
            empty_graph = 0;
            }
        else if(!strcmp(option,"2"))
            {
            add_node_to_array(array);
            print_adjacency_list(array);
            empty_graph = 0;
            }
        else if(!strcmp(option,"3"))
            {
            add_verticle_to_array(array);
            print_adjacency_list(array);
            }
        else if(!strcmp(option,"4"))
            {
            printf("Which node do you want to delete?\n");
            printf("Enter name:");

            char* name_buffer = read_string(100);

            if(node_exist(name_buffer,array))
                {
                delete_node_from_array(get_address_by_name(name_buffer, array), array);
                print_adjacency_list(array);
                }
            else 
                {
                printf("Node with that name doesn't exist!\n");
                }
            free(name_buffer);
            }
        else if(!strcmp(option,"5"))
            {
            printf("Which verticle do you want to delete?\n");
            printf("Enter first node name:");

            char* first_name_buffer = read_string(100);

            printf("Enter second node name:");
            
            char* second_name_buffer = read_string(100);

            if (node_exist(first_name_buffer,array) && node_exist(second_name_buffer,array))
                {
                Node* f_node = get_address_by_name(first_name_buffer,array);
                Node* s_node = get_address_by_name(second_name_buffer,array);
                delete_verticle(f_node,s_node);
                print_adjacency_list(array);
                }
            else 
                {
                printf("Node with these names don't exist!\n");
                }
            free(first_name_buffer);
            free(second_name_buffer);
            }
        else if (!strcmp(option,"6"))
            {
            printf("Way from which node to which you want to find?\n");
            printf("Enter first node name:");

            char* first_name_buffer = read_string(100);

            printf("Enter second node name:");
            
            char* second_name_buffer = read_string(100);

            if (node_exist(first_name_buffer,array) && node_exist(second_name_buffer,array))
                {
                Node* f_node = get_address_by_name(first_name_buffer,array);
                Node* s_node = get_address_by_name(second_name_buffer,array);
                search_path(f_node,s_node);
                tags_set_default(array);
                }
            else 
                {
                printf("Node with these names don't exist!\n");
                }
            free(first_name_buffer);
            free(second_name_buffer);
            }
        else if (!strcmp(option,"7"))
            {
            printf("The shortest way from which node to which you want to find?\n");
            printf("Enter first node name:");

            char* first_name_buffer = read_string(100);

            printf("Enter second node name:");
            
            char* second_name_buffer = read_string(100);

            if (node_exist(first_name_buffer,array) && node_exist(second_name_buffer,array))
                {
                Node* f_node = get_address_by_name(first_name_buffer,array);
                Node* s_node = get_address_by_name(second_name_buffer,array);
                search_shortest_path(f_node,s_node,array);
                tags_set_default(array);
                shortest_ways_set_default(array);
                }
            else 
                {
                printf("Node with these names don't exist!\n");
                }
            free(first_name_buffer);
            free(second_name_buffer);
            }
        else if (!strcmp(option,"8"))
            {
            components(array);
            }
        else if(!strcmp(option,"9"))
            {
            if(empty_graph == 0)
                {
                delete_node_array(array);
                empty_graph = 1;
                }
            array = new_node_array();
            construct_node_array(array);
            int empty_graph = 1;
            }
        else if (!strcmp(option,"0"))
            {
            if(empty_graph == 0)
                {
                delete_node_array(array);
                }
            free(option);
            return;
            }
        else
            {
            printf("Wrong input!\n");
            }
        free(option);
        }
    }

int main()
    {
    run_menu();
    }