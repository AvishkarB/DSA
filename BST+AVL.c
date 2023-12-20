#include <stdio.h>
#include <stdlib.h>
#include <time.h> //time is included to generate different random numbers every runtime

//creating a struct for the nodes in the tree
struct node
{
    int data; //stores the key assigned to that node
    int height; //stores the height of the node from the bottom i.e. leaf nodes have height = 0 and root node has maximum height
    struct node* left; //left child of the node
    struct node* right; //right child of the node
};

//initialising the struct node as a leaf node
struct node* constructor(int elem)
{
    struct node* root = (struct node*) calloc(1, sizeof(struct node));
    root->data = elem;
    root->height = 0; //leaf nodes have height = 0
    root->left = NULL;
    root->right = NULL;

    return root;
}

//defining Maximum function
int Max(int a, int b)
{
    return (a>b) ? a : b;
}

//function to update the height of node
void updateHeight(struct node* root)
{
    //height of root node = max(height of left subtree, height of right subtree) + 1
    root->height = Max((root->left!=NULL) ? root->left->height : -1, (root->right!=NULL) ? root->right->height : -1) + 1;
}

//inserting a key into the BST
struct node* insertBST(struct node* root, int elem)
{
	if(root == NULL)
    {
		root = constructor(elem);
		return root;
	}

	if(elem < root->data)
        root->left = insertBST(root->left,elem);
	else
        root->right = insertBST(root->right, elem);
    
    updateHeight(root);
	return root;
}

//finds the minimum value in a tree
int minValue(struct node* root)
{
	struct node* temp = root;
	while(temp->left != NULL) //minimum value = leftmost node in the Binary Search Tree
        temp = temp->left;
	
    return temp->data;
}

//deleting a key from the tree
struct node* deleteBST(struct node* root, int elem)
{
	if(root == NULL)
        return NULL;

	if(elem < root->data)
		root->left = deleteBST(root->left, elem);
	else if(elem > root->data)
		root->right = deleteBST(root->right, elem);
	else
    {
		//0 children case
		if(root->left == NULL && root->right == NULL)
        {
            struct node* temp = root;
            root = NULL;
            free(temp);
            return root;
		}
		//1 child case
		else if(root->left != NULL && root->right == NULL)
        {
			struct node* temp = root;
            root = root->left; //transplant left subtree to the root
            free(temp);
		}
		else if(root->left == NULL && root->right != NULL)
        {
			struct node* temp = root;
            root = root->right; //transplant right subtree to the root
            free(temp);
		}
		//2 children case
		else
        {
			int min = minValue(root->right); //find the successor of the root
			root->data = min; //replace the root with its successor
			root->right = deleteBST(root->right, min); //delete the successor from the right subtree
		}
	}

    updateHeight(root);
    return root;
}

//returns the height difference between right and left subtrees
int getHeightDiff(struct node* root)
{
    return ((root->right != NULL) ? root->right->height : -1) - ((root->left != NULL) ? root->left->height : -1);
}

//left rotate node
struct node* leftRotation(struct node* root)
{
    struct node* rightChild = root->right;
    struct node* rightChild_leftChild = rightChild->left;

    root->right = rightChild_leftChild;
    rightChild->left = root;
    
    updateHeight(root);
    updateHeight(rightChild);

    return rightChild;
}

//right rotate node
struct node* rightRotation(struct node* root)
{
    struct node* leftChild = root->left;
    struct node* leftChild_rightChild = leftChild->right;

    root->left = leftChild_rightChild;
    leftChild->right = root;

    updateHeight(root);
    updateHeight(leftChild);

    return leftChild;
}

//balancing the tree
struct node* balanceAVL(struct node* root, int heightDiff)
{
    if(heightDiff > 1)
    {   
        if(getHeightDiff(root->right) > 0) 
        {
            //right-right heavy case
            return leftRotation(root);
        }
        else
        {
            //right-left heavy case
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    else
    {
        if(getHeightDiff(root->left) < 0)
        {
            //left-left heavy case
            return rightRotation(root);
        }
        else
        {
            //left-right heavy case
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
}

//inserting a key into the AVL
struct node* insertAVL(struct node* root, int elem)
{
	if(root == NULL)
    {
		root = constructor(elem);
		return root;
	}

	if(elem < root->data)
        root->left = insertAVL(root->left, elem);
	else
        root->right = insertAVL(root->right, elem);
    
    updateHeight(root);

    //balancing the AVL, recursively upwards from leaf to root
    int heightDiff = getHeightDiff(root);
    if(heightDiff > 1 || heightDiff < -1)
        return balanceAVL(root, heightDiff);
	else
	    return root;

}

//deleting a key from the AVL
struct node* deleteAVL(struct node* root, int elem)
{
	if(root == NULL)
        return NULL;

	if(elem < root->data)
		root->left = deleteAVL(root->left, elem);
	else if(elem > root->data)
		root->right = deleteAVL(root->right, elem);
	else
    {
		//0 children case
		if(root->left == NULL && root->right == NULL)
        {
            struct node* temp = root;
            root = NULL;
            free(temp);
            return root;
		}
		//1 child case
		else if(root->left != NULL && root->right == NULL)
        {
			struct node* temp = root;
            root = root->left; //transplant left subtree to the root
            free(temp);
		}
		else if(root->left == NULL && root->right != NULL)
        {
			struct node* temp = root;
            root = root->right; //transplant right subtree to the root
            free(temp);
		}
		//2 children case
		else
        {
			int min = minValue(root->right); //find the successor of the root
			root->data = min; //replace the root with its successor
			root->right = deleteAVL(root->right, min); //delete the successor from the right subtree
		}
	}

    updateHeight(root);

    ////balancing the AVL, recursively upwards from leaf to root
    int heightDiff = getHeightDiff(root);
    if(heightDiff > 1 || heightDiff < -1)
        return balanceAVL(root, heightDiff);
	else
	    return root;

}

int main()
{
    FILE* inputFile = fopen("input.txt", "w+");

    struct node* rootBST = NULL;
    struct node* rootAVL = NULL;
    int arr[1000];
    int map[1000] = {0};

    srand(time(0));
    for(int j=0;j<1000;j++) {
        int random1 = rand();
        int random2 = rand();
        arr[j] = (int)(random1*random2);
        fprintf(inputFile, "%d\n", arr[j]);

        rootBST = insertBST(rootBST, arr[j]);
        rootAVL = insertAVL(rootAVL, arr[j]);
    }

    printf("Height after BST insertion = %d\n", rootBST->height);
    printf("Height after AVL insertion = %d\n", rootAVL->height);

    for(int j=0;j<100;j++) {
        int random1 = rand();
        int random2 = rand();
        int rand_0to999 = ((int)(random1*random2))%1000;

        if(map[rand_0to999] == 1)
            j--;
        else
        {
            map[rand_0to999] = 1;
            rootBST = deleteBST(rootBST, arr[rand_0to999]);
            rootAVL = deleteAVL(rootAVL, arr[rand_0to999]);
        }
    }

    printf("Height after BST deletion = %d\n", rootBST->height);
    printf("Height after AVL deletion = %d\n", rootAVL->height);

    fclose(inputFile);
    return 0;
}