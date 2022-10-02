/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include "leet.h"

struct ListNode *swap_node(struct ListNode *head)
{
	struct ListNode *resutl;

	resutl = head->next;
	head->next = head->next->next;
	resutl->next = head;

	return resutl;
}

struct ListNode *swapPairs(struct ListNode *head)
{
	struct ListNode *tmp1;
	struct ListNode *tmp2;
	struct ListNode **pp;

	if (NULL == head || NULL == head->next)
		return head;

	tmp1 = head;
	pp = &head;
	do {
		tmp2 = swap_node(tmp1);
		*pp = tmp2;
		pp = &tmp1->next;
		tmp1 = tmp1->next;
	} while (tmp1 != NULL && tmp1->next != NULL);

	return head;
}
