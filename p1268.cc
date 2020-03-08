#include "common.h"
struct TrieNode{
	TrieNode() {
		index = -1;
        children = vector<TrieNode*>(26, nullptr);
    }
	int index;
    vector<TrieNode*> children;
};
struct Trie{
	Trie() {
		root = new TrieNode();
	}
	~Trie() {
		erase(root);
	}
    void insert(const string& s, int index)
    {
        TrieNode* current = root;
		for(auto c : s) {
			int i = c - 'a';
			if (!current->children[i]) {
				current->children[i] = new TrieNode();
			}
			current = current->children[i];
		}
		current->index = index;
    }
	 void suggestedProducts(vector<vector<string>>&result, const string& s, const vector<string>& products) {
        int n = s.size();
		TrieNode* start = root;
		for (int i = 0; i < n; ++i) {
			vector<string> temp;
			start = helper(start, s, i, temp, products);
			result.emplace_back(temp);
		}
    }
	TrieNode* helper(TrieNode* start, const string& s, int index, vector<string>& result, const vector<string>& products) {
		if (!start) {
			return start;
		}
		// begin with "start", target s[index]
        int next = s[index] - 'a';
        TrieNode* ret = start->children[next];
        if (ret) {
			// do dfs
            stack<TrieNode*> stk;
			stk.push(ret);
			while(!stk.empty()) {
				auto current = stk.top();
				stk.pop();
				if (current->index >= 0) {
					result.push_back(products[current->index]);
				}
                if (result.size() == 3) {
                    break;
                }
                auto& v = current->children;
                for (int i = v.size() - 1; i >= 0; --i) {
					if (v[i]) {
						stk.push(v[i]);
					}
				}
            }
		}
        return ret;
    }


    private:
	TrieNode* root;
	void erase(TrieNode* root) {
		if(!root) {
			return;
		}
		for(auto& c : root->children) {
			if (c) {
				erase(c);
			}
		}
		delete root;
	}
};
class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
		sort(products.begin(), products.end());
		string prefix;
		vector<vector<string>> result;
		for (size_t i = 0; i < searchWord.size(); ++i) {
			result.push_back({});
			auto&v = result.back();
			prefix.push_back(searchWord[i]);
			auto it = lower_bound(products.begin(), products.end(), prefix);
            for (; it < products.end(); ++it) {
                if (it->substr(0, i + 1) == prefix) {
					v.push_back(*it);
					if (v.size() == 3) {
						break;
					}
				} else {
					break;
				}
            }
        }
		return result;
	}
};
	
class Solution_my {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
		Trie t;
		for(size_t i = 0; i < products.size(); ++i) {
			t.insert(products[i], i);
		}
        vector<vector<string>> result;
        t.suggestedProducts(result, searchWord, products);
		return result;
    }
};

int main() {
    vector<string> products = { "mobile", "mouse", "moneypot", "monitor", "mousepad" };
    string searchWord = "mouse";
//	products = {"havana"}, searchWord = "havana";
	//products = {"bags","baggage","banner","box","cloths"}, searchWord = "bags";
	//products = {"havana"}, searchWord = "tatiana";

    Solution s;
	auto r = s.suggestedProducts(products, searchWord);
	for(auto&v : r) {
		displayvector(v);
	}
    return 0;
}
