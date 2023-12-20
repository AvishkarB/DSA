#include <bits/stdc++.h>

node* BST(node* root, int &val) {
	if(root==NULL) {
		root = new node(val);
		return root;
	}
	
	if(val < root->data) root->left = BST(root->left,val);
	else root->right = BST(root->right,val);
	
	return root;
}

bool findInBST(node* root, int val){
	/*if(root==NULL) return false;
	if(root->data == val) return true;

	if(val<root->data) return findInBST(root->left,val);
	else return findInBST(root->right,val);*/

    node* temp = root;
    while(temp!=NULL) {
        if(temp->data==val) return true;
        else if(val<temp->data) temp = temp->left;
        else temp = temp->right;
    }

    return false;
}

int minValueBST(node* root){
	node* temp = root;
	while(temp->left!=NULL) temp = temp->left;
	return temp->data;
}

node* deleteFromBST(node* root, int val) {
	if(root==NULL) return NULL;

	if(val<root->data) {
		root->left = deleteFromBST(root->left,val);
		return root;
	}
	else if(val>root->data) {
		root->right = deleteFromBST(root->right,val);
		return root;
	}
	else {
		//0 children
		if(root->left==NULL && root->right==NULL) {
			delete root;
			return NULL;
		}
		//1 children
		else if(root->left!=NULL && root->right==NULL) {
			node* temp = root->left;
			delete root;
			return temp;
		}
		else if(root->left==NULL && root->right!=NULL) {
			node* temp = root->right;
			delete root;
			return temp;
		}
		//2 children
		else {
			int min = minValueBST(root->right);
			root->data = min;
			root->right = deleteFromBST(root->right,min);
			return root;
		}
	}
}

node* flatten(node* root)
{

    if(root==NULL) return NULL;

    node* curr = root;
    node* temp = new node(-1);
    node* tail = temp;

    while(curr!=NULL) {
        if(curr->left==NULL) {
            tail->right = new node(curr->data);
            tail = tail->right;
            curr = curr->right;
        }
        else {
            node* pre = curr->left;
            while(pre->right!=NULL && pre->right!=curr) pre=pre->right;

            if(pre->right==NULL) {
                pre->right=curr;
                curr = curr->left;
            }
            else {
                pre->right=NULL;
                tail->right = new node(curr->data);
                tail = tail->right;
                curr = curr->right;
            }
        }
    }
    tail = NULL;

    root = temp->right;
    temp->right = NULL;
    temp->left = NULL;
    delete temp;

    return root;
}

int main() {
    int n;
    cin >> n;
    node* root = NULL;
    while(n--){
        int val;
        cin >> val;
        root = BST(root,val);
    }
    levelOrderTraversal(root);
    cout << endl;

    cout << findInBST(root,65) << endl;
    cout << findInBST(root,70) << endl;
    cout << endl;

    root = deleteFromBST(root,65);
    levelOrderTraversal(root);
    cout << endl;
	root = flatten(root);
}