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

void print_Tree_To_File(Point* root, FILE* outfile) {
    if (root == NULL) {
        return;
    }
    
    if (root->label == 'V' || root->label == 'H') {
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

    //close files
    fclose(in_file);
    fclose(out_file1);
    fclose(out_file2);
    fclose(out_file3);

    return EXIT_SUCCESS;
}