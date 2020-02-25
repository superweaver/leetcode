#include "common.h"

unordered_map<int, int> cache;
struct TrieNode{
	int count;
	vector<TrieNode*> children;
	TrieNode(){
		count = 0;
        children = vector<TrieNode*>(26, nullptr);
    }
};
struct Trie{
	Trie() {
		root = new TrieNode;
	}
	~Trie(){
		delete root;
	}
	void insert(int key, int count) {
        //	key &= 0x3FFFFFF;
        auto current = root;
        while (key) {
            int lowbit = key & -key;
			int which = cache[lowbit];	
			if (!current->children[which]) {
				current->children[which] = new TrieNode();
			}
			current = current->children[which];
			key &= ~lowbit;
        }
		current->count += count; // tricky
    }
    int getcount(int key, int firstletter)
    {
        int result = 0;
        //	int firstletter = key >> 26;
        //   key &= 0x3FFFFFF;
        auto current = root;
		bool met = false;
        helper(current, result, firstletter, met , key);
        return result;
    }

private:
    TrieNode * root;
	void helper(TrieNode* current, int&result, int firstletter, bool met, int key) {
        if (!current) {
            return ;
		}
		for (int i = 0; i < 26; ++i) {
			if (current->children[i] && ((key & (1 << i)) == (1 << i)) ) {
                helper(current->children[i], result, firstletter, met || (i == firstletter) , key);
            }
		}
        result += met? current->count : 0;
    }
};
class Solution {
public:
    
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
		// encode information into key
		// the low 26 bits = 1 if there is corresponding character in word s
		//
		// in this question, don't push first letter into bit [26...31]
		// put the first char into bit[31..26] 2^5 = 32, enough to hold it
		//
		// puzzles[i].length == 7, we can ignore some words;
        for (int i = 0; i < 26; ++i) {
            cache[1 << i] = i;
        }
        unordered_map<int, int> count;
		for (auto&s : words) {
			auto key = getkey(s);
			count[key]++;
		}
		count.erase(0);
		Trie t;
		for(auto &p : count) {
            t.insert(p.first, p.second);
        }
		vector<int> result(puzzles.size(), 0);
		for(size_t i = 0; i < puzzles.size(); ++i) {
			auto k = getkey(puzzles[i]);
            result[i] = t.getcount(k, puzzles[i][0] - 'a');
        }
		return result;
    }
private:
	int getkey(string& s) {
		int ones = 0;	
		int key = 0;
		for (auto c : s) {
			int probe = 1 << (c - 'a');
            if ((key & probe) == 0) {
                ones++;
				if (ones > 7) {
					return 0;
				}
            }
			key |=  probe;
        }
		//key += (int(s[0]-'a') << 26);
		return key;
	}
};

int main() {
	// word contains the first letter of puzzle.
    // For each letter in word, that letter is in puzzle.
    // For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage"; while invalid words are "beefed" (doesn't include "a") and "based" (includes "s" which isn't in the puzzle).


    vector<string> words = { "aaaa", "asas", "able", "ability", "actt", "actor", "access" },
                   puzzles = { "aboveyz", "abrodyz", "abslute", "absoryz", "actresz", "gaswxyz" };
	words ={"apple","pleas","please"};
	puzzles = {"aelwxyz","aelpxyz","aelpsxy","saelpxy","xaelpsy"};

    words = { "kkaz", "kaaz", "aazk", "aaaz", "abcdefghijklmnopqrstuvwxyz",
              "kkka", "kkkz", "aaaa", "kkkk", "zzzz" };

    //words = { "kkaz", "kaaz", "aazk", "kkka", "kkkz", "kkkk" };

    puzzles = { "kazxyuv" };

    Solution s;
    displayvector(s.findNumOfValidWords(words, puzzles));
    return 0;
}
