#include <iostream>
using namespace std;

class TrieNode {
	public:
	char data;
	TrieNode* children[26];
	bool isEndOfWord;
	
	TrieNode(char ch){
		data = ch;
		for(int i=0;i<26;i++) children[i] = NULL;
		isEndOfWord = false;
	}
};

class Trie {
	public:
	TrieNode* root;

	Trie(){
		root = new TrieNode('\0');
	}

	void insert(string word){
		TrieNode* temp = root;
        while(word.length()!=0) {
            int index = word[0]-'a';
		
            if(temp->children[index]==NULL) temp->children[index] = new TrieNode(word[0]);

            temp = temp->children[index];
            word = word.substr(1);
        }
        temp->isEndOfWord = true;
	}

	bool search(string word){
		TrieNode* temp = root;
		while(word.length()!=0) {
			int index = word[0]-'a';
		
			if(temp->children[index]==NULL) return false;
	
			temp = temp->children[index];
			word = word.substr(1);
		}
		return temp->isEndOfWord;
	}

    bool startsWith(string prefix) {
		TrieNode* temp = root;
		while(prefix.length()!=0) {
			int index = prefix[0]-'a';
		
			if(temp->children[index]==NULL) return false;
	
			temp = temp->children[index];
			prefix = prefix.substr(1);
		}
		return true;
    }

	TrieNode* deleteWord(TrieNode* root, string word) {
		if(word.length()==0) {
			if(root->isEndOfWord) {
				root->isEndOfWord = false;
				delete root;
				root = NULL;
			}
			return root;
		}

		int index = word[0]-'a';
		root->children[index] = deleteWord(root->children[index],word.substr(1));
		
		int count = 0;
		for(int i=0;i<26;i++) {
			if(root->children[i]!=NULL) count++;
		}

		if(count==0) {
			delete root;
			root = NULL;
		}

		return root;
	}

	void deleteWord(string word){
		root = deleteWord(root,word);
	}
};

int main() {
	Trie* t = new Trie();
	t->insert("hello");
	t->insert("help");
	cout << t->search("hello") << endl;
	cout << t->search("help") << endl;
	t->deleteWord("hello");
	cout << t->search("hello") << endl;
	cout << t->startsWith("hell") << endl;
	cout << t->startsWith("hel") << endl;
}