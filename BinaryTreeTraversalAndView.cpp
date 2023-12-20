#include <bits/stdc++.h>
vector <int> zigZagTraversal(Node* root) {
    vector<int> result;
    queue<Node*> q;
    q.push(root);
    
    bool leftToRight = true;
    
    while(!q.empty()){
        int size = q.size();
        int ans[size] = {0};
        
        for(int i=0;i<size;i++) {
            Node* temp = q.front();
            q.pop();
            int index = leftToRight ? i : size-i-1;
            ans[index] = temp->data;
            
            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }
        
        leftToRight = !leftToRight;
        
        for(int i=0;i<size;i++) result.push_back(ans[i]);
    }
    return result;
}


vector<int> verticalTraversal(Node *root) {
    vector<int> ans;
    map < int, map <int,vector<int>> > nodes;
    queue < pair <Node*, pair<int,int>> > q;
    
    if(root == NULL) return ans;
    
    q.push(make_pair(root,make_pair(0,0)));
    
    while(!q.empty()) {
        pair <Node*, pair<int,int>> temp = q.front();
        q.pop();
        
        Node* tempNode = temp.first;
        int hd = temp.second.first;
        int lvl = temp.second.second;
        
        nodes[hd][lvl].push_back(tempNode->data);
        
        if(tempNode->left) q.push(make_pair(tempNode->left,make_pair(hd-1,lvl+1)));
        if(tempNode->right) q.push(make_pair(tempNode->right,make_pair(hd+1,lvl+1)));
    }
    
    for(auto i:nodes) for(auto j:i.second) for(auto k:j.second) ans.push_back(k);
    
    return ans;
}


vector<int> topView(Node *root)
    {
        vector<int> ans;
        map < int, int > nodes;
        queue < pair <Node*, int> > q;
        
        if(root == NULL) return ans;
        
        q.push(make_pair(root,0));
        
        while(!q.empty()) {
            pair <Node*, int> temp = q.front();
            q.pop();
            
            Node* tempNode = temp.first;
            int hd = temp.second;
            
            if(nodes.find(hd) == nodes.end()) nodes[hd] = tempNode->data;

            if(tempNode->left) q.push(make_pair(tempNode->left,hd-1));
            if(tempNode->right) q.push(make_pair(tempNode->right,hd+1));
        }
        
        for(auto i:nodes) ans.push_back(i.second);
        
        return ans;
    }


vector <int> bottomView(Node *root) {
        vector<int> ans;
        map < int, int > nodes;
        queue < pair <Node*, int> > q;
        
        if(root == NULL) return ans;
        
        q.push(make_pair(root,0));
        
        while(!q.empty()) {
            pair <Node*, int> temp = q.front();
            q.pop();
            
            Node* tempNode = temp.first;
            int hd = temp.second;
            
            nodes[hd] = tempNode->data;

            if(tempNode->left) q.push(make_pair(tempNode->left,hd-1));
            if(tempNode->right) q.push(make_pair(tempNode->right,hd+1));
        }
        
        for(auto i:nodes) ans.push_back(i.second);
        
        return ans;
    }


vector<int> leftView(Node *root) {
   vector<int> ans;
    map < int, int > nodes;
    queue < pair <Node*, int> > q;
        
    if(root == NULL) return ans;
        
    q.push(make_pair(root,0));
        
    while(!q.empty()) {
        pair <Node*, int> temp = q.front();
        q.pop();
        
        Node* tempNode = temp.first;
        int lvl = temp.second;
        
        nodes[lvl] = tempNode->data;

        if(tempNode->right) q.push(make_pair(tempNode->right,lvl+1));
        if(tempNode->left) q.push(make_pair(tempNode->left,lvl+1));
    }
        
    for(auto i:nodes) ans.push_back(i.second);
        
    return ans;
}
//Faster Left View-
void solve(Node* root, vector<int> &ans, int level) {
    //base case
    if(root == NULL)
        return ;
       
    //we entered into a new level    
    if(level == ans.size())
        ans.push_back(root->data);
        
    solve(root->left, ans, level+1);       
    solve(root->right, ans, level+1);     
}
vector<int> leftView(Node *root)
{
    vector<int> ans;
    solve(root, ans, 0);
    return ans;
}


vector<int> rightView(Node *root)
    {
       vector<int> ans;
        map < int, int > nodes;
        queue < pair <Node*, int> > q;
        
        if(root == NULL) return ans;
        
        q.push(make_pair(root,0));
        
        while(!q.empty()) {
            pair <Node*, int> temp = q.front();
            q.pop();
            
            Node* tempNode = temp.first;
            int lvl = temp.second;
            
            nodes[lvl] = tempNode->data;

            if(tempNode->left) q.push(make_pair(tempNode->left,lvl+1));
            if(tempNode->right) q.push(make_pair(tempNode->right,lvl+1));
        }
        
        for(auto i:nodes) ans.push_back(i.second);
        
        return ans;
    }
//Faster Right View-
void solve(Node* root, vector<int> &ans, int level) {
    //base case
    if(root == NULL)
        return ;
       
    //we entered into a new level    
    if(level == ans.size())
        ans.push_back(root->data);
        
    solve(root->right, ans, level+1);    
    solve(root->left, ans, level+1); 
}  
vector<int> rightView(Node *root)
{
    vector<int> ans;
    solve(root, ans, 0);
    return ans;
}

//Boundary Traversal-
void traverseLeft(Node* root, vector<int> &ans) {
        //base case
        if( (root == NULL) || (root->left == NULL && root->right == NULL) ) return;
            
        ans.push_back(root->data);
        if(root->left) traverseLeft(root->left, ans);
        else traverseLeft(root->right, ans);
            
    }   
void traverseLeaf(Node* root, vector<int> &ans) {
    //base case
    if(root == NULL) return;
        
    if(root->left == NULL && root->right == NULL) {
        ans.push_back(root->data);
        return;
    }
    
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
    
}    
void traverseRight(Node* root, vector<int> &ans) {
    //base case
    if( (root == NULL) || (root->left == NULL && root->right == NULL) ) return;
    
    if(root->right) traverseRight(root->right, ans);
    else traverseRight(root->left, ans);  
    //wapas aagye
    ans.push_back(root->data);
        
}    
vector <int> boundaryTraversal(Node *root)
{
    vector<int> ans;
    if(root == NULL)
        return ans;
        
    ans.push_back(root->data);
    
    //left part print/store
    traverseLeft(root->left, ans);
    
    //traverse Leaf Nodes
    
    //left subtree
    traverseLeaf(root->left, ans);
    //right subtree
    traverseLeaf(root->right, ans);
    
    //traverse right part
    traverseRight(root->right, ans);
    
    return ans;  
}