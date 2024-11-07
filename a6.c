#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define SIZE 1000

typedef struct Point {
    int label;    
    int x;
    int y;
    int x_point;
    int y_point;
    struct Point *left;
    struct Point *right;
} Point;

//global variables
// int arr_index2 = 0; //used for part 2
// int arr_index3 = 0; //used for part 3

void free_tree(Point* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void free_array(Point** arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL) {
            // Don't free nodes that are part of the tree
            if (arr[i]->left == NULL && arr[i]->right == NULL) {
                free(arr[i]);
            }
            arr[i] = NULL;
        }
    }
}

void cleanup_memory(Point** arr, int arr_index) {
    if (arr_index > 0 && arr[arr_index - 1] != NULL) {
        free_tree(arr[arr_index - 1]); // Free the root and all its children
    }
    
    // Free any remaining standalone nodes
    free_array(arr, SIZE);
}

void print_pre(Point* node, FILE* outfile) {
    if (node == NULL) 
    {
        return;
    }
    //visit the root
    if (node->label == 'V' || node->label == 'H') 
    {
        fprintf(outfile, "%c(%d,%d)\n", node->label, node->x, node->y);
    } 
    else 
    {
        // For other nodes, print label with coordinates as before
        fprintf(outfile, "%d(%d,%d)\n", node->label, node->x, node->y);
    }

    //traverse the left subtree
    print_pre(node->left, outfile);

    //traverse the right subtree
    print_pre(node->right, outfile);
}

void print_dim(Point* node, FILE* outfile) {
    if (node == NULL) {
        return;
    }

    //traverse the left subtree
    print_dim(node->left, outfile);

    //traverse the right subtree
    print_dim(node->right, outfile);

    //visit the root
    if (node->label == 86 || node->label == 72) 
    {
        fprintf(outfile, "%c(%d,%d)\n", node->label, node->x, node->y);
    } 
    else 
    {

        fprintf(outfile, "%d(%d,%d)\n", node->label, node->x, node->y);
    }
}

Point** add_To_Array(Point* newPoint, int arr_ind, Point** arr) {
    if (arr_ind >= SIZE) {
        free(newPoint);
        return NULL; //array bounds check
    }
    arr[arr_ind] = newPoint;
    return arr;
}

Point** add_To_Tree(int arr_index, Point** arr) {
    int i = 0;
    while (i < arr_index) {
        //if its a 'V' or 'H' node and have at least two nodes before it
        if ((arr[i]->x == -1) && (i >= 2)) {
            Point* current = arr[i];
            Point* right = arr[i - 1];
            Point* left = arr[i - 2];
            
            //set the current node's children
            current->right = right;
            current->left = left;

            // Shift nodes left by 2 to consolidate
            for (int j = i - 2; j < arr_index - 2; j++) {
                arr[j] = arr[j + 2];
            }

            arr[arr_index - 2] = current;

            // Adjust array size after connecting two children
            arr_index -= 2;
            i -= 1; // Move `i` back to re-evaluate current node as it has moved

            // for (int k = 0; k < arr_index; k++) 
            // {
            //     if (arr[k]->label == 'V' || arr[k]->label == 'H') {
            //         printf("%c\n", arr[k]->label);
            //     } else {
            //         printf("%d\n", arr[k]->label);
            //     }
            // }
            // printf("\n");

            // If `i` now points to the last node, we have built the root
            if (i == arr_index) {
                return arr;
            }
        } else {
            i++;
        }
    }
    return arr;
}

Point** find_VHdim(int arr_index, Point** arr) {
    int i = 0;
    while (i < arr_index) {
        //if its a 'V' or 'H' node and have at least two nodes before it
        if ((arr[i]->x == -1) && (i >= 2)) {
            Point* current = arr[i];
            Point* right = arr[i - 1];
            Point* left = arr[i - 2];
            
            //set the current node's children
            current->right = right;
            current->left = left;


            //new part
            if (current->label == 'V' && current->x == -1) {
                current->x = (current->right)->x + (current->left)->x;
                if  ((current->right)->y >= ((current->left)->y)) {
                    current->y = (current->right)->y;
                }
                else {
                    current->y = (current->left)->y; 
                } 
            }
            else if (current->label == 'H' && current->x == -1) {
                current->y = (current->right)->y + (current->left)->y;

                if  ((current->right)->x >= ((current->left)->x)) {
                    current->x = (current->right)->x;
                }
                else {
                    current->x = (current->left)->x; 
                } 
            }

            // Shift nodes left by 2 to consolidate
            for (int j = i - 2; j < arr_index - 2; j++) {
                arr[j] = arr[j + 2];
            }

            arr[arr_index - 2] = current;

            // Adjust array size after connecting two children
            arr_index -= 2;
            i -= 1; // Move `i` back to re-evaluate current node as it has moved

            // If `i` now points to the last node, we have built the root
            if (i == arr_index) {
                // for (int k = 0; k < arr_index; k++) 
                // {
                //     if (arr[k]->label == 'V' || arr[k]->label == 'H') {
                //         printf("%c(%d,%d)\n", arr[k]->label, arr[k]->x, arr[k]->y);
                //     } else {
                //         printf("%d(%d,%d)\n", arr[k]->label, arr[k]->x, arr[k]->y);
                //     }
                // }
                // printf("\n");

                return arr;
            }
        } else {
            i++;
        }
    }
    return arr;
}

// Point** find_VHdim(int arr_index, Point** arr) {
        
//     int i = 0;
//     while (i < arr_index) { 
//         if ((arr[i]->label == 'V' || arr[i]->label == 'H') && (arr_index >= 2)) {
//         arr[i]->right = arr[i - 1]; 
//         arr[i]->left = arr[i - 2];

//         //new part
//         if (arr[i]->label == 'V') {
//             arr[i]->x = (arr[i]->right)->x + (arr[i]->left)->x;
//             if  ((arr[i]->right)->y >= ((arr[i]->left)->y)) {
//                 arr[i]->y = (arr[i]->right)->y;
//             }
//             else {
//                 arr[i]->y = (arr[i]->left)->y; 
//             } 
//         }
//         else if (arr[i]->label == 'H') {
//             arr[i]->y = (arr[i]->right)->y + (arr[i]->left)->y;

//             if  ((arr[i]->right)->x >= ((arr[i]->left)->x)) {
//                 arr[i]->x = (arr[i]->right)->x;
//             }
//             else {
//                 arr[i]->x = (arr[i]->left)->x; 
//             } 
//         }

//             arr[arr_index2 - 2] = newPoint;
//             arr_index2 = arr_index2 - 1;   
//         }
//         else 
//         {
//             arr_index2++;
//         }
//     }
//     else 
//     {
//         printf("arr is full");
//         free(newPoint);
//     }
//     //at this point tree is fully populated, with VH nodes having dimensions
// }

Point* new_Block(int label, int x_val, int y_val) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->label = label;
    newPoint->x = x_val;
    newPoint->y = y_val;
    newPoint->x_point = -1;
    newPoint->y_point = -1;    
    newPoint->left = NULL;
    newPoint->right = NULL;
    // if (iteration == 1) {
    //     add_To_Array(newPoint, arr_ind, arr);
    // }
    // if (iteration == 2) {    
    //     find_VHdim(newPoint);
    // }
    // if (iteration == 3) {
    //     add_To_Tree_P3(newPoint);
    // }
    return newPoint;
}

Point* new_VH(char label) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->label = label;
    //using -1 to show that it is not an actual dimension
    newPoint->x = -1; 
    newPoint->y = -1; 
    newPoint->x_point = -1;
    newPoint->y_point = -1;   
    newPoint->left = NULL;
    newPoint->right = NULL;
    // if (iteration == 1) {
    //     add_To_Array(newPoint, arr_ind, arr);
    // }
    // if (iteration == 2) {    
    //     find_VHdim(newPoint);
    // }
    // if (iteration == 3) {
    //     add_To_Tree_P3(newPoint);
    // }
    return newPoint;
}

void print_Tree_To_File(Point* root, FILE* outfile) {
    if (root == NULL) {
        return;
    }
    
    if (root->x == -1) {
        fprintf(outfile, "%c\n", (char)root->label);
    }
    else {
        fprintf(outfile, "%d(%d,%d)\n", root->label, root->x, root->y);
    }
    print_Tree_To_File(root->left, outfile);
    print_Tree_To_File(root->right, outfile);
}

void dim_list_To_File(int label, int x_val, int y_val, FILE* outfile) {
    if (label == 'V' || label == 'H') {
        fprintf(outfile, "%c(%d,%d)\n", label, x_val, y_val);
    }
    else {
        fprintf(outfile, "%d(%d,%d)\n", label, x_val, y_val);
    }
}


// void calc_coords(Point* node, int current_x, int current_y) {
//     if (node == NULL){} return;

//     if (node->label != 'V' && node->label != 'H') 
//     {
//         //leaf node (rectangle block)
//         node->x_point = current_x;
//         node->y_point = current_y;
//         return;
//     }

//     if (node->label == 'V') {
//         //vertical cut- left block starts at current position
//         calculate_coordinates(node->left, current_x, current_y);
//         //right block starts after the width of left block
//         calculate_coordinates(node->right, current_x + node->left->x, current_y);
//     }
//     else if (node->label == 'H') {
//         //horizontal cut: bottom block starts at current position
//         calculate_coordinates(node->left, current_x, current_y);
//         //top block starts above the height of bottom block
//         calculate_coordinates(node->right, current_x, current_y + node->left->y);
//     }


// }

int main(int argc, char* argv[])
{    
    //check command line arguments
    if (argc != 5) {
        printf("nah");
        return EXIT_FAILURE;
    }

    //open input and output files
    FILE* in_file = fopen(argv[1], "r");
    FILE* out_file1 = fopen(argv[2], "w");
    FILE* out_file2 = fopen(argv[3], "w");
    FILE* out_file3 = fopen(argv[4], "w");

    if (in_file == NULL || out_file1 == NULL || out_file2 == NULL || out_file3 == NULL) {
        fprintf(stderr, "error opening files\n");
        return EXIT_FAILURE;
    }

    int label = 0;
    char label_VH;
    int x_val = 0;
    int y_val = 0;
    // int iteration = 1; //start with part 1
    int arr_index = 0; //used for part 1
    Point* arr[SIZE] = {NULL};
    Point* newPoint;

    //PART 1
    while (1) {
        if (fscanf(in_file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
            //assings new node
            newPoint = new_Block(label, x_val, y_val); 
            //updates Point* array 
            add_To_Array(newPoint, arr_index, arr); 
            //update index val so it adds next point to next index
            arr_index++; 
        } 
        else if (fscanf(in_file, "%c\n", &label_VH) == 1) {
            //assings new node
            newPoint = new_VH(label_VH);
            //updates Point* array 
            add_To_Array(newPoint, arr_index, arr);
            //update index val so it adds next point to next index
            arr_index++;
        } 
        else {
            break;
        }
    }
    //at this point, Point* arr is fully populated with all the nodes
    // for (int i = 0; i < arr_index; i++) {
    //     if (arr[i]->label == 'V' || arr[i]->label == 'H') {
    //         printf("%c\n", arr[i]->label);
    //     } else {
    //         printf("%d, %d, %d\n", arr[i]->label, arr[i]->x, arr[i]->y);
    //     }
    // }
    // printf("\n");

    //now i gotta create the tree
    //passing in the root node which appears last in postorder
    add_To_Tree(arr_index, arr);
    //at this point tree should be built
    print_pre(arr[arr_index - 1], out_file1);

    //pre-order traversal to out_file1
    // print_Tree_To_File(arr[arr_index - 1], out_file1);

    cleanup_memory(arr, arr_index);

    // // free_remaining_points(arr_index);


    //PART 2
    rewind(in_file); //geeks for geeks, lets me reread from beginning
    arr_index = 0;
    while (1) {
        if (fscanf(in_file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
            newPoint = new_Block(label, x_val, y_val);
            add_To_Array(newPoint, arr_index, arr);
            arr_index++;
            //dim_list_To_File(label, x_val, y_val, out_file2);
        } 
        else if (fscanf(in_file, "%c\n", &label_VH) == 1) {
            newPoint = new_VH(label_VH);
            add_To_Array(newPoint, arr_index, arr);
            arr_index++;

            
            // Point* latest_vh = NULL;
            // for (int j = arr_index - 1; j >= 0; j--) {
            //     if (arr[j]->label == label_VH) {
            //         latest_vh = arr[j];
            //         break;
            //     }
            // }
            
            // if (latest_vh != NULL) {
            //     dim_list_To_File(latest_vh->label, latest_vh->x, latest_vh->y, out_file2);
            //     latest_vh->label = 0;
            // }
        } 
        else {
            break;
        }
    }
    //at this point, Point* arr is fully populated with all the nodes
    // for (int i = 0; i < arr_index; i++) {
    //     if (arr[i]->label == 'V' || arr[i]->label == 'H') {
    //         printf("%c\n", arr[i]->label);
    //     } else {
    //         printf("%d, %d, %d\n", arr[i]->label, arr[i]->x, arr[i]->y);
    //     }
    // }
    // printf("\n");
    find_VHdim(arr_index, arr);
    print_dim(arr[arr_index - 1], out_file2);

    cleanup_memory(arr, arr_index);


    // free_remaining_points(arr_index);

    // if (arr_index2 > 0) {
    // free_tree(arr[arr_index2 - 1]);
    // }
    // free_remaining_points(arr_index2);






    //PART 3-----------------> unfinished
    // rewind(in_file);
    //     while (1) {
    //     if (fscanf(in_file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
    //         newPoint = new_Block(label, x_val, y_val);
    //         add_To_Array(newPoint, arr_index, arr);
    //         arr_index++;
    //     } 
    //     else if (fscanf(in_file, "%c\n", &label_VH) == 1) {
    //         newPoint = new_VH(label_VH);
    //         add_To_Array(newPoint, arr_index, arr);
    //         arr_index++;

    //     } 
    //     else 
    //     {
    //         break;
    //     }
    // }
    // find_VHdim(arr_index, arr);
    // //now ik every dim for every node


    //close files
    fclose(in_file);
    fclose(out_file1);
    fclose(out_file2);
    fclose(out_file3);

    return 0;
}