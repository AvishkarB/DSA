#include <iostream>
#include <queue>
using namespace std;

class node {
  public:
	int data;
	node* left;
	node* right;

	node(int data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}

};

node* buildTree(node* root) {

    int data;
    cin >> data;
    root = new node(data);

    if(data == -1) return NULL;

    cout << "Enter data for inserting in left of " << data << ":" << endl;
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << data << ":" << endl;
    root->right = buildTree(root->right);
    
	return root;
}

void buildLevelOrder(node* &root){
	queue<node*> q;

	cout << "Enter data for root:" << endl;
	int data;
	cin >> data;
	root = new node(data);
	q.push(root);

	while(!q.empty()){
		node* temp = q.front();
		q.pop();

		cout << "Enter left node of " << temp->data << ":" << endl;
		int leftData;
		cin >> leftData;
		if(leftData!=-1) {
			temp->left = new node(leftData);
			q.push(temp->left);
		}

		cout << "Enter right node of " << temp->data << ":" << endl;
		int rightData;
		cin >> rightData;
		if(rightData!=-1) {
			temp->right = new node(rightData);
			q.push(temp->right);
		}
	}
}

void preOrderTraversal(node* root){
	if(root == NULL) return;

	cout << root->data << " ";
	preOrderTraversal(root->left);
	preOrderTraversal(root->right);

	return;
}

void inOrderTraversal(node* root){
	if(root == NULL) return;
	
	inOrderTraversal(root->left);
	cout << root->data << " ";
	inOrderTraversal(root->right);

	return;
}

void postOrderTraversal(node* root){
	if(root == NULL) return;
	
	postOrderTraversal(root->left);
	postOrderTraversal(root->right);
	cout << root->data << " ";

	return;
}

void levelOrderTraversal(node* root){
	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		q.pop();
		
		if(temp == NULL) {
			cout << endl;
			if(!q.empty()) q.push(NULL);
		}
		else {
			cout << temp->data << " ";
			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}
}

void reverseQueue(queue<node*> &q){
	if(q.size()==1) return;

	node* temp = q.front();
	q.pop();
	reverseQueue(q);
	q.push(temp);

	return;
}

void reverseLevelOrderTraversal(node* root){
	queue<node*> q;
	queue<node*> q2;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		q2.push(temp);
		q.pop();
		
		if(temp == NULL) {
			if(!q.empty()) q.push(NULL);
		}
		else {
			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}

	reverseQueue(q2);
	q2.pop();
	
	while(!q2.empty()) {
		node* temp = q2.front();
		if(temp == NULL) cout<<endl;
		else cout << temp->data << " ";
		q2.pop();
	}
	cout<<endl;
}

//Morris Traversal = Inorder Traversal but with space complexity as O(1) instead of O(n)
void morrisTraversal(node* root){
	node* curr = root;

	if(curr==NULL) return;

	while(curr!=NULL) {
		if(curr->left==NULL) {
			cout << curr->data << " ";
			curr = curr->right;
		}
		else {
			node* pre = curr->left;
			while(pre->right!=NULL && pre->right!=curr) pre = pre->right;

			if(pre->right == NULL) {
				pre->right = curr;
				curr = curr->left;
			}
			else {
				cout << curr->data << " ";
				pre->right = NULL;
				curr = curr->right;
			}
		}
	}
	cout << endl;
}

//flatten Binary Tree to Linked List
void flattenToLL(node *root) {
    node* curr = root;

    if(curr==NULL) return;

    while(curr!=NULL) {
        if(curr->left) {
            node* pre = curr->left;
            while(pre->right!=NULL) pre = pre->right;
            
            pre->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }
        curr = curr->right;
    }
}

int main(){
	node* root = NULL;
	cout << "Enter root value:" << endl;
	root = buildTree(root); //1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 -1

	node* root2 = NULL;
	buildLevelOrder(root2); //1 2 3 4 5 6 -1 -1 -1 -1 -1 -1 -1

	preOrderTraversal(root);
	cout << endl;
	inOrderTraversal(root);
	cout << endl;
	postOrderTraversal(root);
	cout << endl;
	levelOrderTraversal(root);
	levelOrderTraversal(root2);
	reverseLevelOrderTraversal(root);
	morrisTraversal(root);
	flattenToLL(root);
}