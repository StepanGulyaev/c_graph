#include "Verticle.h"
#include "Node.h"
#include "Node_array.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Service.h"

Node_array* new_node_array()
    {
    return (Node_array*)calloc(1,sizeof(Node_array));
    }

void construct_node_array(Node_array* to_construct)
    {
    to_construct->size = 0;
    to_construct->node_arr =  calloc(1,sizeof(to_construct->node_arr));
    }

int name_is_unique(char* buffer,Node_array* node_array)
    {
    for(int i = 0; i < node_array->size; i++)
        {
        if(!strcmp(node_array->node_arr[i]->node_id,buffer))
            {
            return 0;
            }
        }
    return 1;
    }

int node_exist(char* buffer,Node_array* node_array)
    {
    for(int i = 0; i < node_array->size; i++)
        {
        if(!strcmp(node_array->node_arr[i]->node_id,buffer))
            {
            return 1;
            }
        }
    return 0;
    }

void add_node_info(Node* node,Node_array* node_array)
    {
    name_error:
    printf("Enter node's unique name:");
    char* buffer = read_string(100);
    buffer = strtok(buffer," ,./;");

    if (name_is_unique(buffer,node_array))
        {
        node->node_id = (char*)calloc(strlen(buffer)+1,sizeof(char));
        strcpy(node->node_id,buffer);
        }
    else
        {
        printf("A node with this name already exist! Try another one\n");
        free(buffer);
        goto name_error;
        }

    free(buffer);
    }



void push_to_array(Node* to_push,Node_array* node_array)
    {
    node_array->size++;
    node_array->node_arr = (Node**)realloc(node_array->node_arr,node_array->size*sizeof(Node*));
    node_array->node_arr[node_array->size -1] = to_push;
    }

Node* get_address_by_name(char* node_name,Node_array* array)
    {
    for(int i = 0; i < array->size; i++)
        {
        if (!strcmp(node_name,array->node_arr[i]->node_id))
            {
            return (array->node_arr[i]);
            }
        }
    return NULL;
    }

void add_node_to_array(Node_array* to_add)
    {
    Node* node = new_node();
    construct_node(node);
    add_node_info(node,to_add);
    push_to_array(node,to_add);
    }

void add_verticle_to_array(Node_array* to_add)
    {
    input_error:
    printf("Enter two nodes verticle connects and verticle's weight.\n");
    printf("(Don't divide info by spaces.Better use node/node/weight format)\n");
    printf("Enter verticle info: ");
    char* buffer = read_string(100);

    char* buffer_s = strtok(buffer," ,./;");

    char* f_node_name = buffer_s;
    buffer_s = strtok(NULL," ,./;");
    char* s_node_name = buffer_s;
    buffer_s = strtok(NULL," ,./;");
    int weight = 0;
    if (buffer_s != NULL) 
        {
        weight = atoi(buffer_s);
        }
    

    if (f_node_name == NULL || s_node_name == NULL)
        {
        printf("Wrong input format!\n");
        free(buffer);
        goto input_error;
        }
    else if(weight == 0)
        {
        printf("Verticle weight can't be 0!\n");
        free(buffer);
        goto input_error;
        }
    else if(!node_exist(f_node_name,to_add) || !node_exist(s_node_name,to_add))
        {
        printf("There is no nodes with names like that!\n");
        free(buffer);
        goto input_error;
        }

    Node* f_node = get_address_by_name(f_node_name,to_add);
    Node* s_node = get_address_by_name(s_node_name,to_add);

    if(get_verticle(f_node,s_node) != NULL)
        {
        choose_to_overwrite:
        printf("Verticle between these nodes already exists, do you want to overwrite it?\n");
        printf("1 - yes, 0 - no: ");
        char* buffer1 = read_string(100);
        if (!strcmp(buffer1,"1"))
            {
            delete_verticle(f_node,s_node);
            create_verticle(f_node,s_node,weight);
            }
        else if (!strcmp(buffer1,"0"))
            {
            free(buffer);
            goto input_error;
            }
        else
            {
            printf("Wrong input!\n");
            free(buffer1);
            goto choose_to_overwrite;
            }
        free(buffer1);
        }
    else
        {
        create_verticle(f_node,s_node,weight);
        }
    free(buffer);
    printf("Verticle created\n");
    }

void build_node_array(Node_array* to_build)
    {
    printf("You're creating nodes now\n");
    while(1)
        {
        printf("Type 1 to create a new node, type 0 to exit: ");
        char* buffer = read_string(100);
        if (!strcmp(buffer,"1"))
            {
            add_node_to_array(to_build);
            }
        else if(!strcmp(buffer,"0"))
            {
            free(buffer);
            break;
            }
        else
            {
            printf("Wrong input!\n");
            }
        printf("Nodes created: ");
        print_node_array(to_build);
        printf("\n");
        free(buffer);
        }

    printf("\n");
    printf("Nodes you have created: ");
    print_node_array(to_build);
    printf("\n");

    printf("Now, create the verticles: \n");
    while(1)
        {
        printf("Type 1 to create a new verticle, type 0 to exit: ");

        char* num_buffer = read_string(100);

        if (!strcmp(num_buffer,"1"))
            {
            add_verticle_to_array(to_build);
            }
        else if(!strcmp(num_buffer,"0"))
            {
            free(num_buffer);
            break;
            }
        else
            {
            printf("Wrong input!\n");
            }
        free(num_buffer);
        }
    }

int get_way_length(Node_array* array)
    {
    int sum = 0;
    for(int i = 0; i < array->size -1; i++)
        {
        sum+= get_verticle(array->node_arr[i],array->node_arr[i+1])->weight;
        }
    return sum;
    }

void print_node_array(Node_array* to_print)
    {
    for(int i = 0; i < to_print->size; i++)
        {
        printf("%s; ",to_print->node_arr[i]->node_id);
        }
    }

void tags_set_default(Node_array* array)
    {
    for(int i = 0; i < array->size;i++)
        {
        array->node_arr[i]->visit_tag = 0;
        }
    }

void shortest_ways_set_default(Node_array* array)
    {
    for(int i = 0; i < array->size;i++)
        {
        array->node_arr[i]->shortest_way_to = INT_MAX;
        }
    }


int is_negaitve_verticles(Node_array* array)
    {
    for(int i = 0; i < array->size;i++)
        {
        for(int j = 0; j < array->node_arr[i]->num_con_vert; j++)
            {
            if(array->node_arr[i]->connected_verticles[j]->weight < 0)
                {
                return 1;
                }
            }
        }
    return 0;
    }

void remove_node_from_array(Node* to_delete,Node_array* node_array)
    {
    int i_to_del = -1;
    for(int i = 0; i < node_array->size; i++)
        {
        if (node_array->node_arr[i] == to_delete)
            {
            i_to_del = i;
            }
        }

    if (i_to_del >= 0 && i_to_del < node_array->size - 1)
        {
        for (int i = i_to_del; i < node_array->size -1;i++)
            {
            node_array->node_arr[i] = node_array->node_arr[i+1];
            }
        node_array->size--;
        node_array->node_arr = (Node**)realloc(node_array->node_arr,node_array->size*sizeof(Node*));
        }
    else if(i_to_del >= 0 && i_to_del == node_array->size - 1)
        {
        node_array->size--;
        node_array->node_arr = (Node**)realloc(node_array->node_arr,node_array->size*sizeof(Node*));
        }
    }

void delete_node_from_array(Node* to_delete,Node_array* node_array)
    {
    int i_to_del = -1;
    for(int i = 0; i < node_array->size; i++)
        {
        if (node_array->node_arr[i] == to_delete)
            {
            i_to_del = i;
            }
        }

    if (i_to_del >= 0 && i_to_del < node_array->size - 1)
        {
        for (int i = i_to_del; i < node_array->size -1;i++)
            {
            node_array->node_arr[i] = node_array->node_arr[i+1];
            }
        node_array->size--;
        node_array->node_arr = (Node**)realloc(node_array->node_arr,node_array->size*sizeof(Node*));
        delete_node(to_delete);
        }
    else if(i_to_del >= 0 && i_to_del == node_array->size - 1)
        {
        node_array->size--;
        node_array->node_arr = (Node**)realloc(node_array->node_arr,node_array->size*sizeof(Node*));
        delete_node(to_delete);
        }
    }

void copy_node_array(Node_array* copy,Node_array* original)
    {
    for(int i = 0; i < original->size; i++)
        {
        push_to_array(original->node_arr[i],copy);
        }
    }

void copy_with_new_nodes(Node_array* copy,Node_array* original)
    {
    for(int i = 0; i < original->size; i++)
        {
        Node* node = new_node();
        construct_node(node);
        node->node_id = (char*)calloc(strlen(original->node_arr[i]->node_id)+1,sizeof(char));
        strcpy(node->node_id,original->node_arr[i]->node_id);
        node->shortest_way_to = original->node_arr[i]->shortest_way_to;
        node->visit_tag = original->node_arr[i]->visit_tag;
        push_to_array(node,copy);
        }

    for(int i = 0; i < copy->size; i++)
        {
        for(int j = 0; j < original->node_arr[i]->num_con_vert;j++)
            {
            int weight = get_verticle(original->node_arr[i],original->node_arr[i]->connected_nodes[j])->weight;
            if(get_verticle(copy->node_arr[i],get_address_by_name(original->node_arr[i]->connected_nodes[j]->node_id,copy)) == NULL)
                {
                create_verticle(copy->node_arr[i],get_address_by_name(original->node_arr[i]->connected_nodes[j]->node_id,copy),weight);
                }
            }
        }
    }

void desc_way(Node_array* to_delete_ways_array,Node* node)
    {
    for(int i = 0; i < node->num_con_vert;i++)
        {
        if(node->shortest_way_to + node->connected_verticles[i]->weight <= node->connected_nodes[i]->shortest_way_to)
            { 
            node->connected_nodes[i]->shortest_way_to = node->shortest_way_to + node->connected_verticles[i]->weight;
            push_to_array(node->connected_nodes[i],to_delete_ways_array);
            }
        }
    }

void delete_node_array(Node_array* to_delete)
    {
    for(int i = 0;i < to_delete->size; i++)
        {
        if(to_delete->node_arr[i] != NULL)
            {
            delete_node(to_delete->node_arr[i]);
            }
        }
    free(to_delete->node_arr);
    free(to_delete);
    }