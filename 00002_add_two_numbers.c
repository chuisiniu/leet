/*
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照
 *  逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * 示例 1：
 *     输入：l1 = [2,4,3], l2 = [5,6,4]
 *     输出：[7,0,8]
 *     解释：342 + 465 = 807.
 * 示例 2：
 *     输入：l1 = [0], l2 = [0]
 *     输出：[0]
 * 示例 3：
 *     输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 *     输出：[8,9,9,9,0,0,0,1]
 */
#include <stdlib.h>
#include <stdarg.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *makeNewNode(int *inc, int num, ...) {
    struct ListNode *result = malloc(sizeof(struct ListNode));
    va_list valist;
    int i;

    result->next = (struct ListNode *)0;
    result->val = 0;

    va_start(valist, num);
    for (i = 0; i < num; i++)
    {
        result->val += va_arg(valist, int);
    }
    /* 清理为 valist 保留的内存 */
    va_end(valist);

    if (result->val > 9) {
        *inc = 1;
        result->val -= 10;
    } else {
        *inc = 0;
    }

    return result;
}

#define ADD_NODE_TO_RESULT(__result__, __tail__, __new__) \
    do {\
        if (!(__result__)) {                                       \
            (__result__) = (__new__);                              \
        }                                                          \
        if ((__tail__)) {                                          \
            (__tail__)->next = (__new__);                          \
        }                                                          \
        (__tail__) = (__new__);                                    \
    } while(0)

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *result = (struct ListNode *)0;
    struct ListNode *tail = result;
    struct ListNode *tmp;
    int inc = 0;

    for (; l1 && l2; l1 = l1->next, l2 = l2->next) {
        tmp = makeNewNode(&inc, 3, l1->val, l2->val, inc);

        ADD_NODE_TO_RESULT(result, tail, tmp);
    }

    if (l2) {
        l1 = l2;
    }

    while (l1) {
        tmp = makeNewNode(&inc, 2, l1->val, inc);

        ADD_NODE_TO_RESULT(result, tail, tmp);

        l1 = l1->next;
    }

    if (inc) {
        tmp = makeNewNode(&inc, 1, inc);

        ADD_NODE_TO_RESULT(result, tail, tmp);
    }

    return result;
}

int main(int argc, char **argv) {
    struct ListNode n11 = {2, 0};
    struct ListNode n12 = {4, 0};
    struct ListNode n13 = {3, 0};
    struct ListNode n21 = {5, 0};
    struct ListNode n22 = {6, 0};
    struct ListNode n23 = {4, 0};
    struct ListNode *res = 0;

    n11.next = &n12;
    n12.next = &n13;
    n21.next = &n22;
    n22.next = &n23;

    res = addTwoNumbers(&n11, &n21);

    exit(0);
}
