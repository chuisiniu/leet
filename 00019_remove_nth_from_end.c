/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
	int cnt;
	struct ListNode *nth_from_end;
	struct ListNode *iter;

	iter = head;
	cnt = 0;
	while (cnt < n && iter) {
		iter = iter->next;
		cnt ++;
	}

	if (cnt < n)
		goto END;

	if (iter == (struct ListNode *)0)
		return head->next;

	nth_from_end = head;
	while (iter->next) {
		iter = iter->next;
		nth_from_end = nth_from_end->next;
	}

	nth_from_end->next = nth_from_end->next->next;

END:
	return head;
}
