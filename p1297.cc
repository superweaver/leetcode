#include "common.h"
struct TrieNode{
	TrieNode(){
		count = 0;	
		children = vector<TrieNode*>(26, 0);
	}
	vector<TrieNode*> children;
	int count;
};
struct Trie {
	Trie() {
		maxCount = 0;
		root = new TrieNode();
	}
	~Trie() {
		erase(root);
	}
	int getMaxCount() {
		return maxCount;
	}
    void insert(string& s, int left, int right, int minSize, int maxSize) {
		// right - left + 1 <= maxSize;
		TrieNode * current = root;
		for (int i = left; i <= right; ++i) {
            auto c = s[i] - 'a';
            if (!current->children[c]) {
				current->children[c] = new TrieNode();
			}
			current = current->children[c];
			if (i - left + 1 >= minSize) {
				current->count++;
				maxCount = max(maxCount, current->count);
			}
			if (i-left + 1 > maxSize) {
                return;
            }
		}
	}

private:
	void erase(TrieNode* root) {
		if (!root) return;
		for (auto c : root->children) {
			if (c ) {
				erase(c);
			}
		}
		delete root;
	}
    TrieNode* root;
    int maxCount;
};
class Solution {
public:
	//https://blog.csdn.net/qq_32424059/article/details/103662574
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
		// maxSize is a redundant condition
		// assume a substring str has less than maxLetters unique letters
		// thn pick its first minSize letters, this smaller substring must have less than maxLetters unique letters
		int result = 0;
		int n = s.size();
		if (n < minSize) {
			return result;
		}
		unordered_map<string, int> count;
		vector<int> cache(128, 0);
		int unique = 0;
		int i = 0;
		// int left = 0;
        for (; i < minSize; ++i) {
            cache[s[i]]++;
			if (cache[s[i]] == 1) {
                unique++;
            }

        }
		
        for (; i <= n; ++i) { // i is not included
			int j = i - minSize; // head
			if (unique <= maxLetters) {
                string str = s.substr(j, minSize);
                int c = ++count[str];
                result = max(result, c);
            }
            if (i < n) {
                cache[s[i]]++;
                if (cache[s[i]] == 1) {
                    unique++;
                }
				cache[s[j]]--;
				if (cache[s[j]] == 0) {
					unique--;
				}
            } else {
                break;
            }
        }
        return result;
	}
    int maxFreq_hash(string s, int maxLetters, int minSize, int maxSize)
    {
        int n = s.size();
        if (n < minSize) {
            return 0;
        }
        // minSize <= n
        int result = 0;
        vector<int> count(128, 0);
        int unique = 0;
        int left = 0;
        int right = -1;
		unordered_map<string, int> cache;
        while (true) {
            for (++right; right < n; ++right) {
                count[s[right]]++;
                if (count[s[right]] == 1) {
                    unique++;
                    if (unique == maxLetters + 1) {
                        --count[s[right]];
                        --right;
                        --unique;
                        break;
                    }
                }
            }
            // unique <= maxLetters
            if (unique > 0) {
                if (right == n) {  // !!!
                    --right;
                }
                int len = right - left + 1;
                if (len < minSize) {
                    result += 0;
                } else {
					// len >= minSize
					//int start = left;
                    int end = min(right, left + maxSize - 1);
                    string str = s.substr(left, minSize - 1);
                    for (int j = left + minSize - 1; j <= end; ++j) {
						str.push_back(s[j]);
                        cache[str]++;
                        result = max(result, cache[str]);
                    }
                }
            } else {
                break;
            }
            count[s[left]]--;
            if (count[s[left]] == 0) {
                --unique;
            }
            ++left;
        }
        return result;
    }
    int maxFreq_mine(string s, int maxLetters, int minSize, int maxSize)
    {
		// my solution
        int n = s.size();
        if (n < minSize) {
            return 0;
        }
        // minSize <= n
        int result = 0;
        vector<int> count(128, 0);
        int unique = 0;
        int left = 0;
        int right = -1;
		Trie t;
        while (true) {
            for (++right; right < n; ++right) {
                count[s[right]]++;
                if (count[s[right]] == 1) {
                    unique++;
                    if (unique == maxLetters + 1) {
						--count[s[right]];
                        --right;
                        --unique;
                        break;
                    }
                }
            }
            // unique <= maxLetters
            if (unique > 0) {
                if (right == n) { // !!!
                    --right;
				}
                int len = right - left + 1;
                if (len < minSize) {
                    result += 0;
                } else if (len <= maxSize) {
					t.insert(s, left, right, minSize, maxSize);
                    //int k = (len - minSize + 1); result += k * (k + 1) / 2;
                } else {
					t.insert(s, left, right, minSize, maxSize);
                    // int k = maxSize - minSize + 1; result += k * (k + 1) / 2; result += k * (len - maxSize);
                }
            } else {
                break;
            }
            count[s[left]]--;
            if (count[s[left]] == 0) {
                --unique;
            }
            ++left;
        }
        return t.getMaxCount();
    }
};

int main()
{
    string s = "aababcaab";
    int maxLetters = 2, minSize = 3, maxSize = 4; // 2
	s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3; // 2
	//s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3; // 3
	//s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3; // 0
    Solution so;
	cout << so.maxFreq(s, maxLetters, minSize, maxSize) << endl;
    return 0;
}
