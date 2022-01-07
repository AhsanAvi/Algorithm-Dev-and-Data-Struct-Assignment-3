/** 
 * • Name: Ahsan Ali (aliahsa)
 * • Assignment: Assignment 3
 * 
 * • This program implements a binary search tree
 * • KNOWN ISSUES: for program 2, when there are matches while searching,
        the match count hits returns 1000, instead of the true value
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//BSTREE defines a type which is a pointer to a node
typedef struct node *BSTREE;

//node contains data, pointer to left and right child
struct node
{
	int data;
	BSTREE left;
	BSTREE right;
};

//The following are functions that you will need to define below
BSTREE insert(BSTREE root, int number);
BSTREE find(BSTREE root, int number);
void inOrderTraversal(BSTREE subtree, FILE *fp);


int main()
{
	//Create a pointer call root, which points to the root of the tree;
	//Initially, root points to NULL
	BSTREE root = NULL;

    FILE *iOfile = fopen("inOrderTraversal.txt", "w");
    FILE *file = fopen("dataToBuildTree.txt", "r");
    FILE *searchFile = fopen("searchList.txt", "r");
    int counter = 0, num = 0;
    clock_t start;
    clock_t end;
    printf("what is the size: ");
    int size = 0; scanf("%d", &size);
    //getting size of input from user for size

    // comment out when switching between algorithms
    // // =================question 2, part a=================//
    for (int i = 1; i <= size; i++) {
        root = insert(root,i);
    }
    start = clock();
    for (int i=1; i<1001; i++) {
        fscanf(searchFile, "%d", &num); //pulling next number from file
        if(find(root, num) != NULL) { //searching pulled number from file
            counter++;
        }
    }
    end = clock();
    double time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%d matched lines", counter);
    printf("\ntime taken %f \n", time);
    inOrderTraversal(root, iOfile);
    // uncomment to see output of traversal

    
    // comment out when switching between algorithms
    // =================question 2, part b=================//
    // if (file == NULL) {
    //     puts("cannot open file");
    // }
    // num = 0; counter = 1;
    // fscanf(file, "%d", &num);
    // while (!feof(file) && counter < size){
    //     fscanf(file, "%d", &num);
    //     //reading next number from file
    //     root = insert(root, num);
    //     //inserting number into bst
    //     counter++;
    //     //preferred using while loop to make sure the file
    //     //does not hit eof
    // }
    // counter = 0;
    // start = clock();
    // for (int i=1; i<1001; i++) {
    //     fscanf(searchFile, "%d", &num); //pulling next number from file
    //     if(find(root, num) != NULL) { //searching pulled number from file
    //         counter++;
    //         // keeping track of numbers searched 
    //     }
    // }
    // end = clock();
    // double time = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("%d matched lines", counter);
    // printf("\ntime taken %f \n", time);
    // // inOrderTraversal(root, iOfile);
    // // uncomment to see output of traversal

    fclose(iOfile);
    fclose(file);
    fclose(searchFile);
}

//This function creates a new node whose "data" is number and adds this
//node to the binary search tree rooted at "root"; it returns the root of the tree
BSTREE insert(BSTREE root, int number)
{
	if (root == NULL) {
		//root (of tree or subtree) is empty
        root = (struct node*)malloc(sizeof(struct node));
        root->data = number;
        root->left = NULL;
        root->right = NULL;
        
        //printf("doing null \n");
        return root;
        //storing value in the "new root" of the subtree
	}
	if (number < root->data) {
		root->left = insert(root->left, number);
        //recursing down the left side of the tree until it hits null
        //then save the value entered 
        
        //printf("doing left \n"); 
	}
	else if (number > root->data) {
		root->right = insert(root->right, number);
        //recursing down the right side of the tree until it hits null
        //then save the value entered 
        
        //printf("doing right \n");
	}
	return root;
}


//This function returns a pointer to the node in the tree rooted at "root"
//containing "number" or NULL if "number" is not found
BSTREE find(BSTREE root, int number)
{
    //printf("searching node %d \n", number);
    if (root != NULL) {
        if (number == root->data) {
            //printf("found node %d!!!\n", root->data);
            return root;
        }
        if (number < root->data) {
            return find(root->left, number);
        }
        else if (number > root->data) {
            return find(root->right, number);
        }
        return root;
    }
    else {
        // printf("Node %d is not in tree \n", number);
        return NULL;
    }
}

//This function performs an inorder traversal of the binary
//search tree rooted at "root", by printing to a designated output file the
//values of the nodes as they are visited.
void inOrderTraversal(BSTREE root, FILE *fp)
{
	if (root != NULL) {
        inOrderTraversal(root->left, fp);
        //traversing in order on the left side of the tree
        //printf("%d\n", root->data);
        fprintf(fp, "%d\n", root->data);
        inOrderTraversal(root->right, fp);
        //traversing in order on the right side of the tree
    }
}