#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define SIZE 1000

typedef struct Point {
    int label;    
    int x;
    int y;
    struct Point *left;
    struct Point *right;
} Point;

//global variables
int arr_index = 0; //used for part 1
int arr_index2 = 0; //used for part 2

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

void find_VHdim(Point* newPoint) {
    if (arr_index2 < SIZE) 
    {
        //arr defined in global var section
        arr[arr_index2] = newPoint;

        if ((newPoint->label == 'V' || newPoint->label == 'H') && (arr_index2 >= 2)) {
            newPoint->right = arr[arr_index2 - 1]; 
            newPoint->left = arr[arr_index2 - 2];

            //new part
            newPoint->x = (newPoint->right)->x + (newPoint->left)->x; 
            newPoint->y = (newPoint->right)->y + (newPoint->left)->y; 


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
    newPoint->left = NULL;
    newPoint->right = NULL;
    if (iteration == 1) {
        add_To_Tree(newPoint);
    }
    if (iteration == 2) {    
        find_VHdim(newPoint);
    }
}

void new_VH(char label, int iteration) {
    Point* newPoint = (Point*)malloc(sizeof(Point));
    newPoint->label = label;
    //using -1 to show that it is not an actual dimension
    newPoint->x = -1; 
    newPoint->y = -1; 
    newPoint->left = NULL;
    newPoint->right = NULL;
    if (iteration == 1) {
        add_To_Tree(newPoint);
    }

    if (iteration == 2) {    
        find_VHdim(newPoint);
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
    int iteration = 2;

    //PART 1
    while (!feof(file)) {
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
    //END OF PART 1

    //PART 2
    //iteration++; //now it is iteration 2, for part 2 basically

    //using this while/file open to find dimensions of V/H nodes
    rewind(file);
    while (!feof(file)) {
        if (fscanf(file, "%d(%d,%d)\n", &label, &x_val, &y_val) == 3) {
            new_Block(label, x_val, y_val, iteration);
            dim_list(label, x_val, y_val);
        } 
        else if (fscanf(file, "%c\n", &label_VH) == 1) {
            new_VH(label_VH, iteration);

            for (int j = 0; j < arr_index2 ; j++) {
                if (arr[j]->label == label_VH) {
                    dim_list(arr[j]->label, arr[j]->x, arr[j]->y);
                    arr[j]->label = 0;
                }
            }
        } 
        else 
        {
            //if neither format matched
            break;
        }
    }

    fclose(file);

    return 0;
}