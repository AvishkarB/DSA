#include <bits/stdc++.h>

//Create arrays for each BST from inorder, then merge the arrays and then form BST from the final array
/*void inorder(TreeNode<int> *root, vector<int> &in1) {
    if(root==NULL) return;

    inorder(root->left,in1);
    in1.push_back(root->data);
    inorder(root->right,in1);
}

void merge(vector<int> in1,vector<int> in2,vector<int> &in3) {
    int i=0, j=0;
    while(i<in1.size() && j<in2.size()) {
        if(in1[i]<in2[j]) in3.push_back(in1[i++]);
        else if(in1[i]>in2[j]) in3.push_back(in2[j++]);
        else {
            in3.push_back(in1[i++]);
            in3.push_back(in2[j++]);
        }
    }

    while(i<in1.size()) in3.push_back(in1[i++]);
    while(j<in2.size()) in3.push_back(in2[j++]);
}

TreeNode<int>* inorderToBST(vector<int> &in3, int start, int end) {
    if(start>end) return NULL;

    int mid = start + (end-start)/2;
    TreeNode<int>* root = new TreeNode<int>(in3[mid]);

    root->left = inorderToBST(in3,start,mid-1);
    root->right = inorderToBST(in3,mid+1,end);

    return root;
}

TreeNode<int> *mergeBST(TreeNode<int> *root1, TreeNode<int> *root2){
    vector<int> in1;
    inorder(root1,in1);
    vector<int> in2;
    inorder(root2,in2);

    vector<int> in3;
    merge(in1,in2,in3);

    TreeNode<int>* newroot = inorderToBST(in3,0,in3.size()-1);

    return newroot;
}*/



//Convert each BST to DLL, then merge both DLL and then create BST from DLL
void BST_to_DLL(TreeNode<int>* root, TreeNode<int>* &head){
    if(root == NULL) return;
    
    BST_to_DLL(root->right, head);

    root->right = head;
    if(head) head->left = root;
    head = root;    
    
    BST_to_DLL(root->left, head);
}

TreeNode<int>* merge_DLLs(TreeNode<int>* &head1, TreeNode<int>* &head2){
    TreeNode<int> *head = NULL, *tail = NULL;
    
    if(head1->data < head2->data){
        head = head1;
        tail = head1;
        head1 = head1->right;
    }
    else{
        head = head2;
        tail = head2;
        head2 = head2->right;
    }

    while(head1 && head2){
        if(head1->data < head2->data){
            tail->right = head1;
            head1->left = tail;
            tail = head1;
            head1 = head1->right;
        }
        else{
            tail->right = head2;
            head2->left = tail;
            tail = head2;
            head2 = head2->right;            
        }
    }

    while(head1){
            tail->right = head1;
            head1->left = tail;
            tail = head1;
            head1 = head1->right;
    }
    while(head2){
            tail->right = head2;
            head2->left = tail;
            tail = head2;
            head2 = head2->right;  
    }

    return head;
}

int countNodes(TreeNode<int>* head){
    int count = 0;

    while(head){
        count++;
        head = head->right;
    }
    return count;
}

TreeNode<int>* DLL_to_BST(TreeNode<int>* &head, int n){
    if(n <= 0 || head == NULL) return NULL;

    TreeNode<int>* left = DLL_to_BST(head, n/2);
    
    TreeNode<int>* root = head;
    root->left = left;
    head = head->right;

    root->right = DLL_to_BST(head, n-n/2-1);
    return root;
}

TreeNode<int> *mergeBST(TreeNode<int> *root1, TreeNode<int> *root2){
    TreeNode<int> *head1 = NULL, *head2 = NULL;

    BST_to_DLL(root1, head1); 
    head1->left = NULL;
    
    BST_to_DLL(root2, head2);
    head2->left = NULL;

    head1 = merge_DLLs(head1, head2);
    
    root1 = DLL_to_BST(head1, countNodes(head1));

    return root1;    
}