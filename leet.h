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

static
void print_list(struct ListNode *head)
{
	printf("list %p: ", head);

	while(head) {
		printf("%d ", head->val);

		head = head->next;
	}

	printf("\n");
}
