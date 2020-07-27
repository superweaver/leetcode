#include "common.h"
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        if (!head) {
            return head;
		}
        ListNode dummy(0);
		dummy.next = head;	
		unordered_map<int, ListNode*> prefixsum; // must be unique
		prefixsum[0] = &dummy;
		ListNode*current = head;
		ListNode* pre = &dummy;
		int sum = 0;
        while (current) {
			sum += current->val;	
			// check if sum is in prefixsum
			if(prefixsum.count(sum)) {
				pre = prefixsum[sum];
				int tempsum = sum;
				auto right = current->next;
                while (pre->next != right) {
                    tempsum += pre->next->val;
                    // corner case
                    if (tempsum != sum) {
                        prefixsum.erase(tempsum);
                    }
                    auto remove = pre->next;
                    pre->next = pre->next->next;
					// remove or not?
                    delete remove;
                }
				current = right;
            } else {
				pre = pre->next;
				prefixsum.insert({sum, current});
                current = current->next;
            }
        }
		return dummy.next;
    }
};

int main() {
    vector<int> v = { 1, 2, -3, 3, 1 };
	v = {1,2,3,-3,4};
	v = {1,2,3,-3,-2};
	v = {0, 1,2,3,-3,-2};
    ListNode* head = buildList(v);
	displaylist(head);
    Solution s;
    head = s.removeZeroSumSublists(head);
    displaylist(head);
	deleteList(head);

	return 0;
}

