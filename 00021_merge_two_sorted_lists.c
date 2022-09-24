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

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
#ifndef NULL
#define NULL ((void *)0)
#endif

	struct ListNode *l1;
	struct ListNode *l2;
	struct ListNode *i1;
	struct ListNode *i2;
	struct ListNode *tmp;

	if (NULL == list1)
		return list2;
	if (NULL == list2)
		return list1;

	if (list1->val < list2->val) {
		l1 = list1;
		l2 = list2;
	} else {
		l1 = list2;
		l2 = list1;
	}

	i1 = l1;
	i2 = l2;

	while (i1->next && i2) {
		if (i1->next->val < i2->val) {
			i1 = i1->next;

			continue;
		}

		tmp = i2;
		while (i2->next && i1->next->val >= i2->next->val)
			i2 = i2->next;
		l2 = i2->next;
		i2->next = i1->next;
		i1->next = tmp;
		i2 = l2;
	}

	if (i2)
		i1->next = i2;

	return l1;
}
