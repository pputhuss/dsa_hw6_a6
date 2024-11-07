#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define SIZE 1000000

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
int arr_index = 0; //used for part 1
int arr_index2 = 0; //used for part 2
int arr_index3 = 0; //used for part 3

Point* arr[SIZE];

void free_tree(Point* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void free_remaining_points(int start_index) {
    for (int i = start_index; i < SIZE; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
            arr[i] = NULL;
        }
    }
}

void add_To_Tree(Point* newPoint) {
    if (arr_index < SIZE) 
    {
        //arr defined in global var section
        arr[arr_index] = newPoint; 

        if ((newPoint->x == -1) && (arr_index >= 2)) {
            newPoint->right = arr[arr_index - 1]; 
            newPoint->left = arr[arr_index - 2];

            arr[arr_index - 2] = newPoint;
            arr_index = arr_index - 1;
        }
        else {
            arr_index++;
        }
    }
    else 
    {
        printf("arr is full");
        free(newPoint);
    }
}

void add_To_Tree_P3(Point* newPoint) {
    if (arr_index3 < SIZE) 
    {
        //arr defined in global var section
        arr[arr_index3] = newPoint; 

        if ((newPoint->x == -1) && (arr_index3 >= 2)) {
            newPoint->right = arr[arr_index3 - 1]; 
            newPoint->left = arr[arr_index3 - 2];

            arr[arr_index3 - 2] = newPoint;
            arr_index3 = arr_index3 - 1;
        }
        else {
            arr_index3++;
        }
    }
    else 
    {
        printf("arr is full");
        free(newPoint);
    }
}

void find_VHdim(Point* newPoint) {
    if (arr_index2 < SIZE) 
    {
        arr[arr_index2] = newPoint;

        if ((newPoint->x == -1) && (arr_index2 >= 2)) {
            newPoint->right = arr[arr_index2 - 1]; 
            newPoint->left = arr[arr_index2 - 2];

            //new part
            if (newPoint->label == 86) {
                newPoint->x = (newPoint->right)->x + (newPoint->left)->x;
                if  ((newPoint->right)->y >= ((newPoint->left)->y)) {
                    newPoint->y = (newPoint->right)->y;
                }
                else {
                    newPoint->y = (newPoint->left)->y; 
                } 
            }
            else if (newPoint->label == 72) {
                newPoint->y = (newPoint->right)->y + (newPoint->left)->y;

                if  ((newPoint->right)->x >= ((newPoint->left)->x)) {
                    newPoint->x = (newPoint->right)->x;
                }
                else {
                    newPoint->x = (newPoint->left)->x; 
                } 
            }

            arr[arr_index2 - 2] = newPoint;
            arr_index2 = arr_index2 - 1;   
        }
        else {
            arr_index2++;
        }
    }
    else 
    {
        printf("arr is full");
        free(newPoint);
    }
    //at this point tree is fully populated, with VH nodes having dimensions
}

void new_Block(int label, int x_val, int y_val, int iteration) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->label = label;
    newPoint->x = x_val;
    newPoint->y = y_val;
    newPoint->x_point = -1;
    newPoint->y_point = -1;    
    newPoint->left = NULL;
    newPoint->right = NULL;
    if (iteration == 1) {
        add_To_Tree(newPoint);
    }
    if (iteration == 2) {    
        find_VHdim(newPoint);
    }
    if (iteration == 3) {
        add_To_Tree_P3(newPoint);
    }
}

void new_VH(char label, int iteration) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->label = label;
    //using -1 to show that it is not an actual dimension
    newPoint->x = -1; 
    newPoint->y = -1; 
    newPoint->x_point = -1;
    newPoint->y_point = -1;   
    newPoint->left = NULL;
    newPoint->right = NULL;
    if (iteration == 1) {
        add_To_Tree(newPoint);
    }
    if (iteration == 2) {    
        find_VHdim(newPoint);
    }
    if (iteration == 3) {
        add_To_Tree_P3(newPoint);
    }
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
    if (label == 86 || label == 72) {
        fprintf(outfile, "%c(%d,%d)\n", label, x_val, y_val);
    }
    else {
        fprintf(outfile, "%d(%d,%d)\n", label, x_val, y_val);
    }
}

//global var just for this function
// int right_sub_iteration = 0;
// int packaging_right_side(Point* root, int x_curr, int y_curr) //starts at 0,0 and root btw
// {
//     //first need to get to bottommost V/H node on right subtree
//     //this if is used to make it go right first from node
//     if (right_sub_iteration == 0)
//     {
//         right_sub_iteration = 1;
//         packaging_right_side(root->right, x_curr, y_curr);
//     }
//     else
//     {
//         if ((root->right)->label == 'V' || (root->right)->label == 'H') 
//         {
//             packaging_right_side(root->right, x_curr, y_curr);
//         }
//         else if ((root->left)->label == 'V' || (root->left->label) == 'H')
//         {
//             packaging_right_side(root->left, x_curr, y_curr);
//         }

//         else //if it reaches here the first iteration will be bottommost V/H
//         {
//             //setting bottomost V/H's left node to (0,0)
//             (root->left)->x_point = x_curr; 
//             (root->left)->y_point = y_curr;

//             if(root->label == 'V') 
//             {
//                 root->x_point = (root->left)->x_point;
//                 root->y_point = (root->left)->y_point;

//                 //root->right and root x val updates
//                 (root->right)->x_point = (root->left)->x; //+ (root->left)->x_point;
//                 root->x = (root->left)->x + (root->right)->x; //V's x dim would be leftx + rightx
                
//                 //root->right and root y val updates
//                 //i think the right node will always have the same y for a V cut as left node
//                 (root->right)->y_point = (root->left)->y_point;

//                 //V's y dim would be the highest of the left and right node 
//                 if ((root->right)->y > (root->left)->y) {
//                     root->y = (root->right)->y;
//                 }
//                 else 
//                 {
//                     (root)->y = (root->left)->y;
//                 } //at this point i have gotten the dimensions of V node and set both child nodes
//                 return;

//             }

//         }
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
    int iteration = 1; //start with part 1

    //PART 1
    while (1) {
        if (fscanf(in_file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
            new_Block(label, x_val, y_val, iteration);
        } 
        else if (fscanf(in_file, "%c\n", &label_VH) == 1) {
            new_VH(label_VH, iteration);
        } 
        else {
            break;
        }
    }

    //pre-order traversal to out_file1
    print_Tree_To_File(arr[arr_index - 1], out_file1);

    if (arr_index > 0) {
        free_tree(arr[arr_index - 1]);
    }
    // free_remaining_points(arr_index);

    //PART 2
    rewind(in_file); //geeks for geeks, lets me reread from beginning
    iteration = 2;

    while (1) {
        if (fscanf(in_file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
            new_Block(label, x_val, y_val, iteration);
            dim_list_To_File(label, x_val, y_val, out_file2);
        } 
        else if (fscanf(in_file, "%c\n", &label_VH) == 1) {
            new_VH(label_VH, iteration);
            Point* latest_vh = NULL;
            for (int j = arr_index2 - 1; j >= 0; j--) {
                if (arr[j]->label == label_VH) {
                    latest_vh = arr[j];
                    break;
                }
            }
            
            if (latest_vh != NULL) {
                dim_list_To_File(latest_vh->label, latest_vh->x, latest_vh->y, out_file2);
                latest_vh->label = 0;
            }
        } 
        else {
            break;
        }
    }

    if (arr_index2 > 0) {
    free_tree(arr[arr_index2 - 1]);
    }
    // free_remaining_points(arr_index2);

    //PART 3-----------------> unfinished
    //rewind(in_file);
    //iteration = 3;
    // while (1) {
    //         if (fscanf(in_file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
    //             new_Block(label, x_val, y_val, iteration);
    //         } 
    //         else if (fscanf(in_file, "%c\n", &label_VH) == 1) {
    //             new_VH(label_VH, iteration);
    //         }     
    //         else 
    //         {
    //             //if neither format matched
    //             break;
    //         }
    //     }
    //     //copt of arr_index3 before using if needed, make sure to -1 if u wanna use
    //     int arr_index3_copy = arr_index3;
    //     //at this point tree is created
    //     if ((arr_index3 > 0) && (iteration == 3)) {
    //         //start printing from the last added element (root of the tree)
    //         //doing -1 cuz i did i++ at end of each iteration in add_to_tree
    //         //print_Tree((Point*)arr[arr_index3 - 1]);  // Start printing from the last added element (root of the tree)
    //     }    
    //     int coords = 0;
    //     packaging_right_side((Point*)arr[arr_index3 - 1], 0, 0); //start working from the last added element (root of the tree)
    //     }

    //close files
    fclose(in_file);
    fclose(out_file1);
    fclose(out_file2);
    fclose(out_file3);

    return 0;
}