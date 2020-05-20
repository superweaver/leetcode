#include "common.h"

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> umap;
        for (int i = 0; i < words.size(); i++) {
            umap[words[i]] = i;
        }
        vector<vector<int>> retval;
        for(int i = 0; i < words.size(); i++){
            string r = words[i];
            reverse(r.begin(),r.end());
            // cout<<r<<endl;
            if (umap.count(r) != 0 && !ispal(0, r.size() - 1, r)) {
                // cout<<words[i]<<" "<<r<<endl;
                retval.push_back({i, umap[r]});
            }
            if(words[i] != "" && ispal(0, words[i].size()-1, words[i]) && umap.count("") != 0){
                retval.push_back({i, umap[""]});
                retval.push_back({umap[""],i});
            }
            // cout<<"hello";
            for(int j = 1; j < words[i].size(); j++){

                if(ispal(j, r.size() - 1, r) && umap.count(r.substr(0, j)) != 0){
                    // cout<<"suffix-"<<r.substr(0, j)<<" "<<words[i]<<endl;
                    retval.push_back({umap[r.substr(0, j)],i});
                }


                if(ispal(j, words[i].size() - 1, words[i]) && umap.count(r.substr(words[i].size() - j,j)) != 0){
                    // cout<<"prefix-"<<words[i]<<" "<<r.substr(words[i].size() - j,j)<<endl;
                    retval.push_back({i, umap[r.substr(words[i].size()-j, j)]});
                }

            }
        }
        return retval;
    }

    bool ispal(int s, int e, string& w){
        while(s <= e){
            if (w[s] != w[e]) {
                return false;
            }
            s++;e--;
        }
        return true;
    }
};

int main() {

	Solution s;

	return 0;
}
