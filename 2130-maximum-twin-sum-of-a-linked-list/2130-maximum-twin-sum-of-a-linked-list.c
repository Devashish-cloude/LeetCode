
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int pairSum(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;

    // Find the middle of the linked list
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse the second half
    struct ListNode* prev = NULL;
    struct ListNode* curr = slow;

    while (curr != NULL) {
        struct ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }

    // Calculate the maximum twin sum
    int maxSum = 0;
    struct ListNode* first = head;
    struct ListNode* second = prev;

    while (second != NULL) {
        int sum = first->val + second->val;

        if (sum > maxSum)
            maxSum = sum;

        first = first->next;
        second = second->next;
    }

    return maxSum;
}
