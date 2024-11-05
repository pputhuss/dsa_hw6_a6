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
int arr_index = 0; //used for part 1
int arr_index2 = 0; //used for part 2
int arr_index3 = 0; //used for part 3

Point* arr[SIZE];

void add_To_Tree(Point* newPoint) {
    if (arr_index < SIZE) 
    {
        //arr defined in global var section
        arr[arr_index] = newPoint; 

        if ((newPoint->label == 'V' || newPoint->label == 'H') && (arr_index >= 2)) {
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
    }
}

void add_To_Tree_P3(Point* newPoint) {
    if (arr_index3 < SIZE) 
    {
        //arr defined in global var section
        arr[arr_index3] = newPoint; 

        if ((newPoint->label == 'V' || newPoint->label == 'H') && (arr_index3 >= 2)) {
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
    }
}


void find_VHdim(Point* newPoint) {
    if (arr_index2 < SIZE) 
    {
        //arr defined in global var section
        arr[arr_index2] = newPoint;

        if ((newPoint->label == 'V' || newPoint->label == 'H') && (arr_index2 >= 2)) {
            newPoint->right = arr[arr_index2 - 1]; 
            newPoint->left = arr[arr_index2 - 2];

            //new part
            if (newPoint->label == 'V') {
                newPoint->x = (newPoint->right)->x + (newPoint->left)->x;
                if  ((newPoint->right)->y >= ((newPoint->left)->y)) {
                    newPoint->y = (newPoint->right)->y;
                }
                else {
                    newPoint->y = (newPoint->left)->y; 
                } 
            }
            else if (newPoint->label == 'H') {
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


void print_Tree(Point* root) {
    if (root == NULL) {
        return;
    }
    
    if (root->label == 'V' || root->label == 'H') {
        printf("%c\n", (char)root->label);
    }
    else {
        printf("%d(%d,%d)\n", root->label, root->x, root->y);
    }
    print_Tree(root->left);
    print_Tree(root->right);
}

void dim_list(int label, int x_val, int y_val) {
    if (label == 'V' || label == 'H') {
        printf("%c(%d,%d)\n", label, x_val, y_val);
    }
    else {
        printf("%d(%d,%d)\n", label, x_val, y_val);
    }
}

//global var just for this function
int right_sub_iteration = 0;

int packaging_right_side(Point* root, int x_curr, int y_curr) //starts at 0,0 and root btw
{
    //first need to get to bottommost V/H node on right subtree
    //this if is used to make it go right first from node
    if (right_sub_iteration == 0)
    {
        packaging_right_side(root->right, 0, 0);
        right_sub_iteration = 1;
    }
    else
    {
        if ((root->right)->label == 'V' || (root->right)->label == 'H') 
        {
            packaging_right_side(root->right, 0, 0);
        }
        else if ((root->left)->label == 'V' || (root->left->label) == 'H')
        {
            packaging_right_side(root->left, 0, 0);
        }

        else //if it reaches here the first iteration will be bottommost V/H
        {
            //setting bottomost V/H's left node to (0,0)
            (root->left)->x_point = x_curr; 
            (root->left)->y_point = y_curr;

            if(root->label == 'V') 
            {
                (root->right)->x_point = (root->left)->x + (root->left)->x_point;
                
                //i think the right node will always have the same y for a V cut as left node
                (root->right)->y_point = (root->left)->y;
                // if ((root->right)->y > (root->left)->y) {
                //     (root->right)->y_point = (root->right)->y;
                // }
                // else 
                // {
                //     (root->right)->y_point = (root->left)->y;

                // }
            }

        }
    }
}

int main(int argc, char* argv[])
{    
    char filename[] = "input.txt"; //i just put input.txt for now

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return -1; //did not work
    }

    int label = 0; //number label
    char label_VH;
    int x_val = 0; //block x dim
    int y_val = 0; //block y dim
    int iteration = 3;

    //PART 1
    if (iteration == 1) {
        while (1) {
            if (fscanf(file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
                new_Block(label, x_val, y_val, iteration);
            } 
            else if (fscanf(file, "%c\n", &label_VH) == 1) {
                new_VH(label_VH, iteration);
            } 
            else 
            {
                //if neither format matched
                break;
            }
        }

        if ((arr_index > 0) && (iteration == 1)) {
            //start printing from the last added element (root of the tree)
            //doing -1 cuz i did i++ at end of each iteration in add_to_tree
            print_Tree((Point*)arr[arr_index - 1]);  // Start printing from the last added element (root of the tree)
        }
    }
    //END OF PART 1

    //PART 2
    //iteration++; //now it is iteration 2, for part 2 basically

    //using this while/file open to find dimensions of V/H nodes
    else if (iteration == 2) {
        // rewind(file);
        while (1) {
            if (fscanf(file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
                new_Block(label, x_val, y_val, iteration);
                dim_list(label, x_val, y_val);
            } 
            else if (fscanf(file, "%c\n", &label_VH) == 1) {
                new_VH(label_VH, iteration);
                //find the most recently processed VH node with this label
                Point* latest_vh = NULL;
                for (int j = arr_index2 - 1; j >= 0; j--) {  //search backwards
                    if (arr[j]->label == label_VH) {
                        latest_vh = arr[j];
                        break;  //take only the most recent one
                    }
                }
                
                if (latest_vh != NULL) {
                    dim_list(latest_vh->label, latest_vh->x, latest_vh->y);
                    latest_vh->label = 0;  //clearing it so it skips this one next time
                }
            } 
            else 
            {
                //if neither format matched
                break;
            }
        }
    }
    
    //PART 3
    else if (iteration == 3) {
        // rewind(file);
        while (1) {
            if (fscanf(file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
                new_Block(label, x_val, y_val, iteration);
            } 
            else if (fscanf(file, "%c\n", &label_VH) == 1) {
                new_VH(label_VH, iteration);
            } 
            
            else 
            {
                //if neither format matched
                break;
            }
        }
        //copt of arr_index3 before using if needed, make sure to -1 if u wanna use
        int arr_index3_copy = arr_index3;

        //at this point tree is created
        if ((arr_index3 > 0) && (iteration == 3)) {
            //start printing from the last added element (root of the tree)
            //doing -1 cuz i did i++ at end of each iteration in add_to_tree
            //print_Tree((Point*)arr[arr_index3 - 1]);  // Start printing from the last added element (root of the tree)
        }    
        int coords = 0;
        coords = packaging_right_side((Point*)arr[arr_index3 - 1], 0, 0); //start working from the last added element (root of the tree)






        }

    else 
    {
        fclose(file);
    }
    
    fclose(file);

    return 0;
}