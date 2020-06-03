#include "common.h"
struct TrieNode {
	bool isWord;
	int index;
	vector<TrieNode*> children;
	TrieNode() :isWord(false), index(INT_MIN), children(26, nullptr) {}
};
class Trie {
public:
	Trie() {
		root = new TrieNode;
	}
	~Trie() {
		erase(root);
	}
	void insert(const string& s, int index) {
		int pre = -1;
		int n = s.size();
		TrieNode* current = root;
		for (int j = n - 1; j >= 0; --j) {
			if (!current->children[s[j] - 'a']) {
				current->children[s[j] - 'a'] = new TrieNode;
			}
			current = current->children[s[j] - 'a'];
		}
		current->isWord = true;
		current->index = index;
	}
	void visit(const string& s, int index, vector<int>& parent) {
		int n = s.size();
		TrieNode* current = root;
		for (int j = n - 1; j >= 0; --j) {
			current = current->children[s[j] - 'a'];
			if (j > 0 && current->isWord) {
				parent[current->index] = 0;
			}
		}
		if (index != current->index) { // repeated
			parent[index] = 0;
		}
	}
private:
	TrieNode* root;
	void erase(TrieNode* node) {
		if (!node) {
			return;
		}
		for (auto p : node->children) {
			if (p) {
				erase(p);
			}
		}
		delete(node);
	}
};
class Solution {
public:
	int minimumLengthEncoding(vector<string>& words) {
		int n = words.size();
		Trie tree;
		vector<int> parent(n, 1);
		for (int i = 0; i < n; ++i) {
            // insert from back to front
            // words with same suffix can be combined
			tree.insert(words[i], i);
		}
		for (int i = 0; i < n; ++i) {
			if (parent[i]) {
				tree.visit(words[i], i, parent);
			}
		}
		int r = 0;
		for(int i = 0; i < n; ++i){
			if(parent[i]){
				r += words[i].size() + 1;
			}
		}
		return r;
	}
};

int main() {
    vector<string> words = {"time", "me", "bell"};

	Solution s;
    cout << s.minimumLengthEncoding(words) << endl;
	return 0;
}
