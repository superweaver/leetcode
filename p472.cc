#include "common.h"
//https://massivealgorithms.blogspot.com/2016/12/leetcode-472-concatenated-words.html
//https://www.cnblogs.com/EdwardLiu/p/6213426.htm://www.cnblogs.com/EdwardLiu/p/6213426.html/
//https://blog.csdn.net/magicbean2/article/details/78626138
//https://www.cnblogs.com/grandyang/p/6254527.html
class Trie {
    public:
        /** Initialize your data structure here. */
        Trie() {

        }
        /** Inserts a word into the trie. */
        void insert(const string& word) {
            node* p = &top;
            for (size_t i = 0; i < word.size(); ++i) {
                if (p->v[word[i] - 'a'] != nullptr) {
                    p =  p->v[word[i] - 'a'] ;
                } else {
                    p->v[word[i] - 'a'] = new node();
                    p =  p->v[word[i] - 'a'] ;
                }
            }
            p->end = true;
        }

        /** Returns if the word is in the trie. */
        bool search(string word) {
            node* p = &top;
            for (size_t i = 0; i < word.size(); ++i) {
                if (p->v[word[i] - 'a'] != nullptr) {
                    p =  p->v[word[i] - 'a'] ;
                } else {
                    return false;
                }
            }
            return p->end;
        }

        /** Returns if there is any word in the trie that starts with the given prefix. */
        bool startsWith(string prefix) {
            node* p = &top;
            for (size_t i = 0; i < prefix.size(); ++i) {
                if (p->v[prefix[i] - 'a'] != nullptr) {
                    p =  p->v[prefix[i] - 'a'] ;
                } else {
                    return false;
                }
            }
            return true;
        }
        // check if a string is a concatenated words by other words in Trie
        bool check(const string& w, int start = 0, int count = 0) {
            if (w.empty()) return false;
            node* cur = &top;
            for (size_t i = start; i < w.size(); i++) {
                auto next = cur->v[w[i]-'a'];
                if (!next) return false;
                if (next->end) {
                    // hard here
                    // must check here
                    if (i == w.size() - 1 ) {
                        return count >=1;
                    }
                    if (check(w, i+1, count + 1)) {
                        return true;
                    }
                }
                cur = next;
            }
            // important
            return false;
        }
    private:
        struct node{
            vector<node*> v;
            bool end;   // if there is a word ending at node
            node(){
                end = false;
                v = vector<node*>(26, nullptr);
            }
            bool isEmpty() {
                for (auto p : v) {
                    if (p) {
                        return false;
                    }
                }
                return true;

            }
        };
        node top;
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        Trie t;
        for (auto& s : words) {
            t.insert(s);
        }
        vector<string> result;
        for (auto& s: words) {
            //cout << t.check("velbhj");
            if (t.check(s)) {
                result.push_back(s);
            }
        }
    return result;
    }
};


int main() {

	Solution s;

	return 0;
}
