#include "common.h"
struct TrieNode {
	bool isWord;
	vector<TrieNode*> children;
	TrieNode(){
		children = vector<TrieNode*>(26, nullptr);
		isWord = false;
	}
};
class Trie {
	public:
		Trie (){
			root = new TrieNode();
		}
		void insert(const string& w, bool reverse = false) {
			TrieNode* current = root;
			int n = w.size();
			for (int i = 0; i < n; ++i) {
				int j = reverse ? n - 1 - i : i;
				auto& child = current->children[w[j] - 'a'];
				if (!child) {
					child = new TrieNode();
				}
				current = child;
			}
			current->isWord = true;
		}
		bool check (const string& w, int len) {
			// check if string of last len characters of w from right to left passed a node with isWord == true;
			TrieNode* current = root;
			int n = w.size();
			for (int j = n - 1; j > n - 1 - len; --j) {
				auto& child = current->children[w[j] - 'a'];
				if (!child) {
					return false;
				}
				current = child;
				if (current->isWord) {
					return true;
				}
			}
			return false;
		}
		bool exist(const string& w) {
			TrieNode* current = root;
			for (auto c : w) {
				auto& child = current->children[c - 'a'];
				if (!child) {
					return false;
				}
			}
			return current->isWord;
		}
		~Trie() {
			erase(root);
		}
	private:
		void erase(TrieNode* root) {
			if (!root) {
				for (auto & c : root->children) {
					if (c) {
						erase(c);
					}
				}
				delete root;
				root = nullptr;
			}
		}
		TrieNode* root;
};
class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
		maxLen = 0;
		for (auto&s : words) {
			t.insert(s, true);
			maxLen = max(maxLen, s.size());
		}
	}
	bool query(char letter) {
		past.push_back(letter);	
		int upper = min(past.size(), maxLen);
		return t.check(past, upper);
		
	}
private:
	Trie t;
	size_t maxLen;
	string past;

};
	
int main() {
	vector<string> words{"abaa","abaab","aabbb","bab","ab"};
	vector<vector<string>> input = {{"a"},{"a"},{"b"},{"b"},{"b"},{"a"},{"a"},{"b"},{"b"},{"a"},{"a"},{"a"},{"a"},{"b"},{"a"},{"b"},{"b"},{"b"},{"a"},{"b"},{"b"},{"b"},{"a"},{"a"},{"a"},{"a"},{"a"},{"b"},{"a"},{"b"},{"b"},{"b"},{"a"},{"a"},{"b"},{"b"},{"b"},{"a"},{"b"},{"a"}};
	vector<bool> ans;
	vector<bool> expected = {false,false,true,false,true,false,false,true,false,false,false,false,false,true,false,true,false,false,false,true,false,false,false,false,false,false,false,true,false,true,false,false,false,false,true,false,true,false,true,false};
	StreamChecker sc(words);
	int i = 0;
	for (auto &s : input) {
		ans.push_back(sc.query(s[0][0]));
		if (ans.back() != expected[i]) {
			cout << " error " << i << endl;
		}
		++i;
	}
	
 

	return 0;
}
