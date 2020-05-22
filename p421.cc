#include "common.h"
// not solved
// 1) https://kingsfish.github.io/2017/12/15/Leetcode-421-Maximum-XOR-of-Two-Numbers-in-an-Array/
// a^b = c, then a^c = a ^(a^b) = b;
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        int mask = 0;

        for (int i = 31; i >= 0; i--) {
            mask = mask | ( 1 << i);
            unordered_set<int> s;
            for(auto num:nums){
                s.insert(num&mask);
            }
            // assume bit i is 1;
            // for any of n in s, check if test^n is also in set;
            int test = result | (1 << i);
            for(auto n:s) {
                if (s.count(test^n)) {
                    result = test;
                    break;
                }
            }
            // else bit i = 0;
        }
        return result;
    }
};
// 2) trie: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91059/java-on-solution-using-trie
struct TrieNode {
    TrieNode* child[2];
    TrieNode(){
        child[0] = nullptr;
        child[1] = nullptr;
    }
};
void destroyTrieNode(TrieNode* root) {
    if (!root) return;
    destroyTrieNode(root->child[0]);
    destroyTrieNode(root->child[1]);
    delete root;
    root = nullptr;
}

class Solution2 {
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = INT_MIN;
        int mask = 0;
        TrieNode* root = new TrieNode();
        for (auto num: nums) {
           TrieNode* current = root;
            for(int i = 31; i >= 0; --i) {
                int bit_i = (num >> i) & 1;  // 0 or 1
                if (current->child[bit_i] == nullptr) {
                    current->child[bit_i] = new TrieNode();
                }
                current = current->child[bit_i];
            }
        }
        for (auto num: nums) {
             TrieNode* current = root;
             int localRes = 0;
             for(int i = 31; i >= 0; --i) {
                int bit_i = (num >> i) & 1;  // 0 or 1
                if (current->child[1^bit_i]!= nullptr){
                    current = current->child[1^bit_i];
                    // set localRes bit i
                    localRes |= (1 << i);
                } else {
                    current = current->child[bit_i];
                }
             }
            result = max(result, localRes);
        }


        destroyTrieNode(root);
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
