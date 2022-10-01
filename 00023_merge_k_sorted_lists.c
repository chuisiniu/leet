/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(_arr) (sizeof(_arr) / sizeof(_arr[0]))
#endif

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_list(struct ListNode *head)
{
	printf("list %p: ", head);

	while(head) {
		printf("%d ", head->val);

		head = head->next;
	}

	printf("\n");
}

void print_list_array(struct ListNode **lists, int n)
{
	int i;

	printf("array begin\n");
	for (i = 0; i < n; i++)
		print_list(lists[i]);
	printf("array end\n");
}

void quick_sort_k_lists(struct ListNode **lists, int size)
{
	int mid;
	int s;
	int e;
	struct ListNode *tmp;
	int s_pre;
	int e_pre;

	if (size < 2)
		return;

	mid = 0;

	s = 1;
	e = size - 1;
	s_pre = s;
	e_pre = e;

	while (s < e) {
		while (lists[s]->val <= lists[mid]->val && s < e)
			s++;
		while (lists[e]->val >= lists[mid]->val && s < e)
			e--;

		if (s < e && lists[s]->val > lists[mid]->val
			&& lists[e]->val < lists[mid]->val) {
			tmp = lists[s];
			lists[s] = lists[e];
			lists[e] = tmp;
		} else if (s < e && lists[s]->val > lists[mid]->val) {
			tmp = lists[mid];
			lists[mid] = lists[s];
			lists[s] = tmp;
			mid = s;
			s = mid + 1;
		} else if (s < e && lists[e]->val < lists[mid]->val) {
			tmp = lists[mid];
			lists[mid] = lists[e];
			lists[e] = tmp;
			mid = e;
			e = mid - 1;
		}
	}

	if (lists[s]->val <= lists[mid]->val) {
		tmp = lists[s];
		lists[s] = lists[mid];
		lists[mid] = tmp;
		mid = s;
	} else if (s > 1) {
		tmp = lists[s - 1];
		lists[s - 1] = lists[mid];
		lists[mid] = tmp;
		mid = s - 1;
	}

	quick_sort_k_lists(lists, mid);
	quick_sort_k_lists(lists + mid + 1, size - mid - 1);
}

struct ListNode *mergeKLists_slow(struct ListNode **lists, int listsSize)
{
	struct ListNode *i1;
	struct ListNode *i2;
	struct ListNode *tmp;
	struct ListNode *result;
	int i;
	int min;

	for (i = 0; i < listsSize;) {
		if (lists[i] == NULL) {
			listsSize--;
			lists[i] = lists[listsSize];
		} else
			i++;
	}

	if (listsSize == 0)
		return NULL;
	if (listsSize == 1)
		return lists[0];

	quick_sort_k_lists(lists, listsSize);
	result = lists[0];

	while (lists[0]->next && lists[0]->next->val < lists[1]->val)
		lists[0] = lists[0]->next;

	if (NULL == lists[0]->next) {
		lists[0]->next = lists[listsSize - 1];
		listsSize -= 1;
	}

	if (listsSize == 1)
		return result;

	i1 = lists[0];
	i2 = lists[1];
	while (i1->next && i2) {
		if (i1->next->val < i2->val) {
			i1 = i1->next;

			if (NULL == i1->next) {
				lists[1] = i2->next;
				i2->next = NULL;
				i1->next = i2;

				goto POP;
			}
			continue;
		}

		tmp = i2;
		while (i2->next && i1->next->val >= i2->next->val &&
			   (listsSize < 3 || (NULL == lists[2]) || lists[2]->val >= i2->next->val))
			i2 = i2->next;
		lists[1] = i2->next;
		i2->next = i1->next;
		i1->next = tmp;
		i1 = i2;

	POP:
		for (i = 2; i < listsSize; i++) {
			if (NULL == lists[i - 1] || lists[i - 1]->val > lists[i]->val) {
				tmp = lists[i - 1];
				lists[i - 1] = lists[i];
				lists[i] = tmp;
			} else {
				break;
			}
		}
		if (NULL == lists[i - 1])
			listsSize -= 1;
		i2 = lists[1];
	}

	if (lists[1])
		i1->next = lists[1];

	return result;
}

struct ListNode *mergeKLists_slow1(struct ListNode **lists, int listsSize)
{
	struct ListNode *tmp;
	struct ListNode *result;
	struct ListNode *p;
	int i;
	int j;

	for (i = 0; i < listsSize;) {
		if (lists[i] == NULL) {
			listsSize--;
			lists[i] = lists[listsSize];
		} else
			i++;
	}

	if (listsSize == 0)
		return NULL;
	if (listsSize == 1)
		return lists[0];

	quick_sort_k_lists(lists, listsSize);
	result = lists[0];

	while (1 < listsSize) {
		for (i = 0; i < listsSize - 1; i++) {
			print_list(result);
			print_list_array(lists, listsSize);
			if (lists[i]->val > lists[i + 1]->val) {
				tmp = lists[i];
				lists[i] = lists[i + 1];
				lists[i + 1] = lists[i + 1]->next;
				lists[i]->next = tmp;

				if (lists[i + 1] == NULL) {
					for (j = i + 1; j < listsSize - 1; j++)
						lists[j]= lists[j + 1];
					listsSize -= 1;
				}
			} else {
				p = lists[i];
				while (p->next && p->next->val <= lists[i + 1]->val)
					p = p->next;

				if (i == 0)
					lists[i] = lists[i + 1];
				// lists[i] 全部小于 lists[i + 1]
				if (NULL == p->next) {
					p->next = lists[i + 1];
					for (j = i + 1; j < listsSize - 1; j++)
						lists[j]= lists[j + 1];
					listsSize -= 1;
				} else {
					tmp = p->next;
					p->next = lists[i + 1];
					lists[i + 1] = lists[i + 1]->next;
					p->next->next = tmp;

					// lists[i + 1] 被取空了
					if (lists[i + 1] == NULL) {
						for (j = i + 1; j < listsSize - 1; j++)
							lists[j]= lists[j + 1];
						listsSize -= 1;
					}
				}
			}
		}
	}

	return result;
}

struct ListNode *mergeKLists_slow2(struct ListNode **lists, int listsSize)
{
	struct ListNode *result;
	struct ListNode *begin;
	struct ListNode *end;
	struct ListNode *tmp;
	struct ListNode *tmp1;
	int max;
	int i;
	int j;

	for (i = 0; i < listsSize;) {
		if (lists[i] == NULL) {
			listsSize--;
			lists[i] = lists[listsSize];
		} else
			i++;
	}

	if (listsSize == 0)
		return NULL;
	if (listsSize == 1)
		return lists[0];

	quick_sort_k_lists(lists, listsSize);
	result = lists[0];

	while (listsSize > 1) {
		for (i = listsSize - 1; i > 0; i--) {
			if (NULL == lists[i - 1]->next) {
				lists[i - 1]->next = lists[i];
				for (j = i; j < listsSize - 1; j++) {
					lists[j] = lists[j + 1];
				}
				listsSize -= 1;
			} else {
				tmp = lists[i - 1];
				while (tmp->next && tmp->next->val <= lists[i]->val)
					tmp = tmp->next;
				tmp1 = tmp;
				if (NULL == tmp->next) {
					tmp->next = lists[i];
					for (j = i; j < listsSize - 1; j++) {
						lists[j] = lists[j + 1];
					}
					listsSize -= 1;
					continue;
				} else
					tmp = tmp->next;
				max = tmp->val;
				begin = lists[i];
				end = begin;
				while (end->next && end->next->val <= max)
					end = end->next;
				tmp1->next = begin;
				lists[i] = end->next;
				end->next = tmp;
				if (NULL == lists[i]) {
					for (j = i; j < listsSize - 1; j++) {
						lists[j] = lists[j + 1];
					}
					listsSize -= 1;
				}
				if (i == 1) {
					lists[0] = end;
				}
			}
		}
	}

	return result;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
	struct ListNode *result;
	struct ListNode **last_insert;
	struct ListNode *pre;
	struct ListNode *remain_list;
	int remain;
	int i;

	for (i = 0; i < listsSize;) {
		if (lists[i] == NULL) {
			listsSize--;
			lists[i] = lists[listsSize];
		} else
			i++;
	}

	if (listsSize == 0)
		return NULL;
	if (listsSize == 1)
		return lists[0];

	quick_sort_k_lists(lists, listsSize);
	result = lists[0];

	last_insert = malloc(sizeof(struct ListNode *) * listsSize);

	last_insert[0] = lists[0];
	lists[0] = lists[0]->next;
	last_insert[0]->next = NULL;
	remain = lists[0] == NULL ? listsSize - 1 : listsSize;
	for (i = 1; i < listsSize; i++) {
		last_insert[i] = lists[i];
		lists[i] = last_insert[i]->next;
		last_insert[i]->next = NULL;
		last_insert[i - 1]->next = last_insert[i];
		if (NULL == lists[i])
			remain -= 1;
	}

	while (remain > 0) {
		for (i = 0; i < listsSize; i++) {
			if (NULL == lists[i])
				continue;
			pre = last_insert[i];
			while (pre->next && pre->next->val <= lists[i]->val)
				pre = pre->next;
			last_insert[i] = lists[i];
			lists[i] = lists[i]->next;
			last_insert[i]->next = pre->next;
			pre->next = last_insert[i];
			if (NULL == lists[i])
				remain -= 1;
		}
	}

	return result;
}

struct ListNode *array_to_list(int *array, int len)
{
	struct ListNode *head;
	struct ListNode *tail;
	struct ListNode *new;
	int i;

	head = malloc(sizeof(struct ListNode));
	head->val = array[0];
	head->next = NULL;

	tail = head;
	for (i = 1; i < len; i++) {
		new = malloc(sizeof(*new));
		new->val = array[i];
		new->next = NULL;

		tail->next = new;
		tail = new;
	}

	return  head;
}

int main(int argc, char **argv)
{
	struct ListNode *ln_array[10];
	struct ListNode *result;

	goto C1;

	printf("case 0\n");

	int a[] = {1,4,5};
	int b[] = {1,3,4};
	int c[] = {2,6};

	ln_array[2] = array_to_list(a, ARRAY_SIZE(a));
	ln_array[1] = array_to_list(b, ARRAY_SIZE(b));
	ln_array[0] = array_to_list(c, ARRAY_SIZE(c));

	print_list_array(ln_array, 3);

	result = mergeKLists(ln_array, 3);

	print_list(result);
 C1:
	printf("case 1\n");

	int a1[] = {-8,-7,-7,-5,1,1,3,4};
	int b1[] = {-2};
	int c1[] = {-10,-10,-7,0,1,3};
	int d1[] = {2};

	ln_array[3] = array_to_list(d1, ARRAY_SIZE(d1));
	ln_array[2] = array_to_list(c1, ARRAY_SIZE(c1));
	ln_array[1] = array_to_list(b1, ARRAY_SIZE(b1));
	ln_array[0] = array_to_list(a1, ARRAY_SIZE(a1));

	print_list_array(ln_array, 4);

	result = mergeKLists(ln_array, 4);

	print_list(result);

	exit(0);

	printf("case 2\n");
	int a2[] = {-9,-7,-7};
	int b2[] = {-6,-4,-1,1};
	int c2[] = {-6,-5,-2,0,0,1,2};
	int d2[] = {-9,-8,-6,-5,-4,1,2,4};
	int e2[] = {-10};
	int f2[] = {-5,2,3};

	ln_array[5] = array_to_list(f2, ARRAY_SIZE(f2));
	ln_array[4] = array_to_list(e2, ARRAY_SIZE(e2));
	ln_array[3] = array_to_list(d2, ARRAY_SIZE(d2));
	ln_array[2] = array_to_list(c2, ARRAY_SIZE(c2));
	ln_array[1] = array_to_list(b2, ARRAY_SIZE(b2));
	ln_array[0] = array_to_list(a2, ARRAY_SIZE(a2));

	print_list_array(ln_array, 6);

	result = mergeKLists(ln_array, 6);

	print_list(result);

	printf("case 3\n");
	int a3[] = {-5,-4,-3,-1,0,3,3};
	int b3[] = {3,4};
	int c3[] = {-5,-3,-1,3};
	int d3[] = {-8,-6};

	ln_array[3] = array_to_list(d3, ARRAY_SIZE(d3));
	ln_array[2] = array_to_list(c3, ARRAY_SIZE(c3));
	ln_array[1] = array_to_list(b3, ARRAY_SIZE(b3));
	ln_array[0] = array_to_list(a3, ARRAY_SIZE(a3));

	print_list_array(ln_array, 4);

	result = mergeKLists(ln_array, 4);

	print_list(result);

	printf("case 4\n");
	int a4[] = {1,2,3};
	int b4[] = {4,5,6,7};

	ln_array[1] = array_to_list(b4, ARRAY_SIZE(b4));
	ln_array[0] = array_to_list(a4, ARRAY_SIZE(a4));

	print_list_array(ln_array, 2);

	result = mergeKLists(ln_array, 2);

	print_list(result);
 C5:
	printf("case 5\n");
	int a5[] = {-1,1};
	int b5[] = {-3,1,4};
	int c5[] = {-2,-1,0,2};

	ln_array[2] = array_to_list(c5, ARRAY_SIZE(c5));
	ln_array[1] = array_to_list(b5, ARRAY_SIZE(b5));
	ln_array[0] = array_to_list(a5, ARRAY_SIZE(a5));

	print_list_array(ln_array, 3);

	result = mergeKLists(ln_array, 3);

	print_list(result);

C6:
	printf("case 6\n");
	int a6[] = {1};
	int b6[] = {0};

	ln_array[1] = array_to_list(b6, ARRAY_SIZE(b6));
	ln_array[0] = array_to_list(a6, ARRAY_SIZE(a6));

	print_list_array(ln_array, 2);

	result = mergeKLists(ln_array, 2);

	print_list(result);

	exit(0);
}
