#include "common.h"
struct TrieNode{
	TrieNode() {
		children = vector<TrieNode*>(27, nullptr);
		isFolderEnd = false;
	}
	vector<TrieNode*> children;
	bool isFolderEnd;
};
struct Trie{
	Trie(){
		root = new TrieNode();
	}
	~Trie() {
		erase(root);
	}
    void insert(string& s) {
		s.push_back('/');
		int n = s.size();
		TrieNode* current = root;
		char c = 0;
		for (int i = 1; i < n ;) {
            if (s[i] == '/') {
                c = 'z' + 1 - 'a';
            } else {
                c = s[i] - 'a';
            }
            if (!current->children[c]) {
                current->children[c] = new TrieNode();
            }
			current = current->children[c];
			if (s[i] == '/' ) {
				if (i == n - 1) {
                    current->isFolderEnd = true;
					for(auto& c : current->children) {
						if (c) {
                            erase(c);
                        }
					}
                    break;
				}
				if (current->isFolderEnd) {
					s.pop_back();
					return;
				} else {
                    i++;
                }
			} else {
				i++;
			}
		}
		s.pop_back();
	}
    void unfold(vector<string>& result, string& path) {
		unfold(root, result, path);
	}
private:
	TrieNode* root;
	void erase(TrieNode*& root) {
		if (!root) { 
			return;
		}
		for (auto p : root->children) {
			if (p) {
				erase(p);
			}
		}
		delete root;
		root = nullptr;
	}
	void unfold(TrieNode* root, vector<string>& result, string& path) {
        if (!root) {
            return;
        }
		for (size_t i = 0; i < root->children.size(); ++i) {
			if (root->children[i]) {
				path.push_back(i == root->children.size() - 1 ? '/' : ('a' + i));
				unfold(root->children[i], result, path);
				path.pop_back();
			}
		}
        if (root->isFolderEnd) {
            path.pop_back();
            result.push_back(path);
            path.push_back('/');
        }
    }
};
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
		//sort(folder.begin(), folder.end());
		Trie t;
		for(auto&s : folder) {
			t.insert(s);
		}
		string path("/");
		vector<string> result;
		t.unfold(result, path);
		return result;
    }
};

int main() {

    vector<string> folder = { "/a", "/a/b", "/c/d", "/c/d/e", "/c/f" };
	folder = {"/a","/a/b/c","/a/b/d"};
	folder = {"/a/b/c","/a/b/ca","/a/b/d"};

    Solution s;
	displayvector(s.removeSubfolders(folder));
	return 0;
}
