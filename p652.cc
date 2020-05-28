#include "common.h"
// serailiz and then string hash
// or direct hash
class Solution {
public:
    //https://zxi.mytechroad.com/blog/tree/leetcode-652-find-duplicate-subtrees/
    vector<TreeNode*> findDuplicateSubtrees1(TreeNode* root)
    {
        // method 1: convert a subtree to a string and use it as map's key
        unordered_map<string, int> id2count; // subtree's string id to its occurence
        vector<TreeNode*> result;
        getStrID(root, id2count, result);
        return result;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root){
        // similar idear, but use a int64_t as ID
        // how to construct this ID
        // include root's val + the index in the cache of left tree + the inde in the cache of right tree
        unordered_map<int64_t, pair<int, int> > id2index_count; // id of subtree, <index of id in the cache, times>
        vector<TreeNode*> result;
        getIndex(root, id2index_count, result);
        return result;
    }

private:
    string getStrID(TreeNode* root, unordered_map<string, int>& id2count, vector<TreeNode*>& result) {
        if (!root) return "#";
        string strID =
            to_string(root->val) + "," + getStrID(root->left, id2count, result) + "," + getStrID(root->right, id2count, result);
        int times = ++id2count[strID];
        if (times == 2) {
            result.push_back(root);
        }
        return strID;
    }
    int getIndex(TreeNode* root, unordered_map<int64_t, pair<int, int> >& id2index_count,
                 vector<TreeNode*>& result)
    {
        // index serves as a unique id
        if (!root) return 0;
        int64_t key = root->val;
        key += INT_MAX;
        key <<= 32;
        key += (int64_t(getIndex(root->left, id2index_count, result)) << 16) +
               (int64_t(getIndex(root->right, id2index_count, result)));
        /*
                int64_t key = (((int64_t)root->val) << 32) +
                           (int64_t(getIndex(root->left, id2index_count, result)) << 16) +
                           (int64_t(getIndex(root->right, id2index_count, result)));
                           */
        int indexInCache = 0;
        if (id2index_count.count(key) == 0) {
            // new index is id2index_count.size(), an empty slot;
            indexInCache = id2index_count.size() + 1;
            int occurances = 1;
           // cout << indexInCache << ":  first" << endl;
            id2index_count[key] = make_pair(indexInCache, occurances);
        } else {
            pair<int, int>& p = id2index_count[key];
            indexInCache = p.first;
            //cout << indexInCache << ": repeated" << endl;
            int occurances = ++p.second;
            if (occurances == 2) {
                result.push_back(root);
            }
        }
        return indexInCache;
    }
};


int main() {

	Solution s;

	return 0;
}
