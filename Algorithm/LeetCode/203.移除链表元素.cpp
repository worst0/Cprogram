/*
 * @lc app=leetcode.cn id=203 lang=cpp
 *
 * [203] 移除链表元素
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) return head;
        ListNode dummy, *p = &dummy;
        dummy.next = head;
        while (p->next) {
            if (p->next->val == val) p->next = p->next->next;
            else p = p->next;
        }
        return dummy.next;

    }
};
// @lc code=end

