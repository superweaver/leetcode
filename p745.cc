#include "common.h"
//https://zxi.mytechroad.com/blog/tree/leetcode-745-prefix-and-suffix-search/
//https://www.cnblogs.com/grandyang/p/8331660.html
class WordFilter {
public:
	WordFilter(vector<string>& words) {
		int n = words.size();
		for (int i = 0; i < n; ++i) {
			string str = words[i];
			int len = str.size();
			string pre;
			prefix2weight[pre].push_back(i);
			suffix2weight[pre].push_back(i);
			for (int j = 0; j < len; ++j) {
				pre.push_back(str[j]);
				prefix2weight[pre].push_back(i);
				suffix2weight[str.substr(len - 1 - j)].push_back(i);
			}
		}
	}

	int f(string prefix, string suffix) {
		if (prefix2weight.count(prefix) == 0 || suffix2weight.count(suffix) == 0) {
			return -1;
		}
		vector<int>& pre = prefix2weight[prefix];
		vector<int>& suf = suffix2weight[suffix];
		int i = pre.size() - 1;
		int j = suf.size() - 1;
		while (j >= 0 && i >= 0) {
			if (pre[i] > suf[j]) {
				--i;
			}
			else if (pre[i] < suf[j]) {
				--j;
			}
			else {
				return pre[i];
			}
		}
		return -1;
	}
private:
	unordered_map<string, vector<int>> prefix2weight;
	unordered_map<string, vector<int>> suffix2weight;
};
/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */
//https://zxi.mytechroad.com/blog/tree/leetcode-745-prefix-and-suffix-search/
//https://www.cnblogs.com/grandyang/p/8331660.html
class Trie {
public:
	Trie() { root = new TrieNode(); }
	~Trie() {
		erase(root);
	}
	void Insert(const string& s, int index) {
		TrieNode* current = root;
		for(auto c : s) {
			if (!current->children[c - 'a']) {
				current->children[c - 'a'] = new TrieNode();
			}
			current = current->children[c - 'a'];
			// different from normal Trie
			current->index = index;
		}
		current->end = true;
	}
	int startwith(const string& prefix) {
		TrieNode* current = root;
		for (auto c : prefix) {
			if (current->children[c - 'a']) {
				current = current->children[c - 'a'];
			}
			else {
				return -1;
				//return false;
			}
		}
		return current->index;
	}
private:
	struct TrieNode {
		vector<TrieNode*> children;
		bool end;
		int index; // weight;
		TrieNode():end(false), index(-1) {
			children = vector<TrieNode*>(27, nullptr);
			// will use 'z' + 1 for separating suffix and prefix
		}
	};
	void erase(TrieNode*p) {
		if (p) {
			for (auto n : p->children) {
				if (n) {
					erase(n);
				}
			}
			delete p;
		}
	}
	TrieNode* root;
};
class WordFilter2 {
public:
	WordFilter2(vector<string>& words) {
		for(size_t i = 0; i < words.size(); ++i) {
			string s = words[i];
			//trie.Insert(s, i);
			string suffix = string(1, char('z' + 1)) + s;
            trie.Insert(suffix, i); // key, not the original s;
			for (size_t len = 1; len <= s.size(); ++len) {
				trie.Insert(s.substr(s.size() - len) + suffix, i);
			}
		}
	}
	int f(string prefix, string suffix) {
		// clever way !
		return trie.startwith(suffix + string(1, char('z' + 1)) + prefix);
	}
private:
	Trie trie;
};

int main() {

	Solution s;

	return 0;
}
