#include "common.h"
class Solution {
  public:
    vector<int> nextLargerNodes(ListNode *head) {
        if (!head) {
            return {};
        }
        head = reverseList(head);
        // displaylist(head);
        stack<int> s;
        vector<int> result;
        ListNode *current = head;
        while (current) {
            while (!s.empty() && s.top() <= current->val) {
                s.pop();
            }
            if (s.empty()) {
                result.push_back(0);
            } else {
                result.push_back(s.top());
            }
            s.push(current->val);
            current = current->next;
        }
        reverse(result.begin(), result.end());
        head = reverseList(head);
        // displaylist(head);
        return result;
    }

  private:
    ListNode *reverseList(ListNode *head) {
        if (!head) {
            return head;
        }
        ListNode *Pre = nullptr;
        ListNode *Current = head;
        ListNode *Next = nullptr;
        while (Current) {
            Next = Current->next;
            Current->next = Pre;
            Pre = Current;
            Current = Next;
        }
        return Pre;
    }
};

int main() {

    Solution s;

    return 0;
}
