/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第N个节点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy, *p = &dummy, *q = &dummy;
        dummy.next = head;
        while(n--) p = p->next;
        while (p->next) {
            p = p->next;
            q = q->next;
        }
        q->next = q->next->next;
        return dummy.next;
    }
};
// @lc code=end

