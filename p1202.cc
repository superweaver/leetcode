#include "common.h"
class UF {
public:
    UF(int n)
    {
        d_size = n;
        parent.resize(d_size);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        sizes = vector<int>(d_size, 1);
    }
    int Find(int i)
    {
        while (parent[i] != i) {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }
        return i;
    }
    int getGroups()
    {
        return d_size;
    }
    void Union(int u, int v)
    {
        int uid = Find(u);
        int vid = Find(v);
        if (uid == vid) {
            return;
        }
        int& usize = sizes[uid];
        int& vsize = sizes[vid];
        if (usize < vsize) {
            vsize += usize;
            parent[uid] = vid;
        } else {
            usize += vsize;
            parent[vid] = uid;
        }
        d_size--;
    }

private:
    int d_size;
    vector<int> parent;
    vector<int> sizes;
};
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs)
    {
        int n = s.size();
        UF uf(n);
        for (auto& p : pairs) {
            uf.Union(p[0], p[1]);
        }
        string result(s);
        unordered_map<int, set<int>> g;
        for (auto& p : pairs) {
            int gid = uf.Find(p[0]);
            g[gid].insert(p[0]);
            g[gid].insert(p[1]);
        }
        for (auto& p : g) {
            string sub;
            for (auto i : p.second) {
                sub.push_back(s[i]);
            }
            sort(sub.begin(), sub.end());
            int index = 0;
            for (auto i : p.second) {
                result[i] = sub[index++];
            }
        }
        return result;
    }
};

int main()
{
    string s = "dcab";
    vector<vector<int>> pairs = { { 0, 3 }, { 1, 2 } };  // bacd

    s = "dcab", pairs = { { 0, 3 }, { 1, 2 }, { 0, 2 } };  // abcd
    s = "cba", pairs = { { 0, 1 }, { 1, 2 } };             // abc
    s = "lilsfqpfkrovxrnhxndsqhrtxtsgxcwkvhsgagcqjwcarsvnrwypomwcmmqsxzjrdyloozqbklyjfqfvxsizylzydl"
        "yefqakzroqmosssoxrswwmgqlxipdfswtnonrjdnwaszvswwsuknwocjypgomcsyhkjgojteymueipsdozblnijiws"
        "ahtqriyfsanuyjhngbnb";
    pairs = { { 21, 77 },   { 93, 15 },   { 60, 60 },   { 172, 43 },  { 4, 27 },    { 54, 72 },
              { 125, 43 },  { 57, 139 },  { 179, 127 }, { 83, 50 },   { 22, 50 },   { 28, 92 },
              { 105, 161 }, { 166, 13 },  { 176, 72 },  { 136, 115 }, { 7, 107 },   { 163, 144 },
              { 75, 10 },   { 175, 136 }, { 144, 197 }, { 8, 54 },    { 155, 187 }, { 146, 178 },
              { 109, 106 }, { 3, 20 },    { 1, 76 },    { 112, 21 },  { 182, 161 }, { 7, 155 },
              { 124, 130 }, { 33, 82 },   { 83, 144 },  { 133, 90 },  { 63, 29 },   { 79, 113 },
              { 104, 169 }, { 32, 80 },   { 177, 13 },  { 79, 82 },   { 131, 128 }, { 180, 152 },
              { 3, 48 },    { 154, 44 },  { 21, 117 },  { 180, 41 },  { 167, 104 }, { 128, 195 },
              { 71, 181 },  { 152, 142 }, { 68, 12 },   { 164, 40 },  { 20, 48 },   { 95, 129 },
              { 9, 115 },   { 149, 112 }, { 16, 53 },   { 52, 183 },  { 79, 33 },   { 94, 111 },
              { 92, 61 },   { 33, 130 },  { 35, 143 },  { 35, 145 },  { 53, 19 },   { 23, 57 },
              { 177, 198 }, { 164, 159 }, { 176, 177 }, { 153, 151 }, { 182, 65 },  { 103, 138 },
              { 23, 90 },   { 13, 119 },  { 164, 100 }, { 84, 105 },  { 25, 89 },   { 51, 164 },
              { 151, 146 }, { 134, 137 }, { 185, 132 }, { 68, 134 },  { 31, 45 },   { 180, 106 },
              { 139, 187 }, { 125, 14 },  { 65, 73 },   { 2, 193 },   { 129, 29 },  { 25, 166 },
              { 29, 92 },   { 179, 140 }, { 99, 107 },  { 189, 138 }, { 151, 92 },  { 130, 170 },
              { 84, 169 },  { 194, 62 },  { 65, 13 },   { 119, 105 }, { 184, 59 },  { 193, 8 },
              { 29, 26 },   { 166, 11 },  { 144, 37 },  { 143, 93 },  { 170, 15 },  { 138, 132 },
              { 96, 102 },  { 36, 123 },  { 144, 12 },  { 84, 117 },  { 154, 2 },   { 133, 107 },
              { 162, 11 },  { 163, 98 },  { 189, 142 }, { 58, 43 },   { 85, 74 },   { 22, 66 },
              { 191, 176 }, { 28, 62 },   { 71, 58 },   { 146, 8 },   { 30, 78 },   { 16, 7 },
              { 121, 137 }, { 14, 1 },    { 97, 187 },  { 44, 112 },  { 35, 0 },    { 68, 83 },
              { 108, 133 }, { 86, 121 },  { 90, 180 },  { 164, 77 },  { 57, 41 },   { 108, 40 },
              { 156, 194 }, { 62, 16 },   { 117, 168 }, { 30, 184 },  { 59, 157 },  { 133, 65 },
              { 18, 144 },  { 140, 97 },  { 190, 75 },  { 152, 178 }, { 145, 116 }, { 55, 70 },
              { 66, 100 },  { 2, 74 },    { 161, 44 },  { 144, 114 }, { 171, 155 }, { 83, 116 },
              { 80, 87 },   { 100, 126 }, { 121, 5 },   { 92, 70 },   { 62, 49 },   { 106, 77 },
              { 25, 91 },   { 15, 127 },  { 166, 56 },  { 182, 43 },  { 45, 85 },   { 9, 67 },
              { 6, 186 },   { 128, 180 }, { 167, 59 },  { 0, 100 },   { 160, 79 },  { 107, 189 },
              { 146, 81 },  { 70, 83 },   { 109, 164 }, { 21, 87 },   { 77, 153 },  { 21, 185 },
              { 42, 27 },   { 169, 182 }, { 164, 6 },   { 87, 194 },  { 165, 87 },  { 161, 39 },
              { 92, 149 },  { 73, 168 },  { 131, 5 },   { 153, 20 },  { 163, 149 }, { 165, 1 },
              { 182, 28 },  { 88, 129 },  { 24, 53 },   { 158, 70 },  { 170, 8 },   { 39, 14 },
              { 59, 182 },  { 152, 36 } };

    Solution so;
	cout << s[63] << endl;
    cout << so.smallestStringWithSwaps(s, pairs) << endl;
    return 0;
}
