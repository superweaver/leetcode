#include "common.h"

class Solution {
   public:
    string entityParser(string text) {
        // &quot; -> "
        // &apos; -> '
        // &amp; -> &
        // &gt; -> >
        // &lt; -> <
        // &frasl; -> /
        size_t n = text.size();
        vector<string> cache{"&quot;", "&apos;", "&amp;",
                             "&gt;",   "&lt;",   "&frasl;"};
        vector<string> replace{"\"", "\'", "&", ">", "<", "/"};

        string result;
        for (size_t i = 0; i < n;) {
            if (text[i] != '&') {
                result.push_back(text[i]);
                ++i;
            } else {
                while (i + 1 < n && text[i + 1] == '&') {
                    result.push_back('&');
                    ++i;
                }
                // i < n && text[i] == &
                bool match = false;
                for (size_t j = 0; j < cache.size(); ++j) {
                    const auto s = cache[j];
                    if (i + s.size() <= n && text.substr(i, s.size()) == s) {
                        result += replace[j];
                        i += s.size();
                        match = true;
                        break;
                    }
                }
                if (!match) {
                    result.push_back('&');
                    ++i;
                }
            }
        }
        return result;
    }
};

int main() {
    string text = "&amp; is an HTML entity but &ambassador; is not.";
    text = "and I quote: &quot;...&quot;";
    // text = "x &gt; y &amp;&amp; x &lt; y is always false";
    text = "leetcode.com&frasl;problemset&frasl;all";

    Solution s;
    cout << s.entityParser(text) << endl;
    return 0;
}
