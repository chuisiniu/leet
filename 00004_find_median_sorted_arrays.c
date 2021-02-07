/*
 * 给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回
 * 这两个正序数组的中位数。
 * 进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？
 * 示例 1：
 *     输入：nums1 = [1,3], nums2 = [2]
 *     输出：2.00000
 *     解释：合并数组 = [1,2,3] ，中位数 2
 * 示例 2：
 *     输入：nums1 = [1,2], nums2 = [3,4]
 *     输出：2.50000
 *     解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 * 示例 3：
 *     输入：nums1 = [0,0], nums2 = [0,0]
 *     输出：0.00000
 * 示例 4：
 *     输入：nums1 = [], nums2 = [1]
 *     输出：1.00000
 * 示例 5：
 *     输入：nums1 = [2], nums2 = []
 *     输出：2.00000
 */
#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int *nums1, int nums1Size,
                              int *nums2, int nums2Size) {
    int i;
    int j;
    int pre;
    int cur;
    int mid;

    mid = (nums1Size + nums2Size) / 2;
    for (i = 0, j = 0, pre = 0, cur = 0; i + j <= mid;) {
        if (j >= nums2Size) {
            if (mid - i - j == 0) {
                pre = cur;
            } else {
                pre = nums1[mid - j -1];
            }
            cur = nums1[mid - j];
            break;
        } else if (i >= nums1Size) {
            if (mid - i - j == 0) {
                pre = cur;
            } else {
                pre = nums2[mid - i -1];
            }
            cur = nums2[mid - i];
            break;
        } else if (nums1[i] < nums2[j]) {
            pre = cur;
            cur = nums1[i];
            i += 1;
        } else {
            pre = cur;
            cur = nums2[j];
            j += 1;
        }
    }

    if (mid * 2 != nums1Size + nums2Size) {
        return (double)cur;
    }
    return ((double)cur + (double)pre)/ 2;
}

double findMedianSortedArrays1(int *nums1, int nums1Size,
                              int *nums2, int nums2Size) {
    int curNums1Size = nums1Size;
    int curNums2Size = nums2Size;
    int *curStart1 = nums1;
    int *curStart2 = nums2;

    double result;

    int remain;
    int kth_min;
    int half_of_k;

    int i;
    int j;
    int *tmp_ptr;
    int tmp;
    int candidate1;
    int candidate2;

    if (nums1Size == 1 && nums2Size == 1) {
        return (double)(nums1[0] + nums2[0]) / 2;
    }

#define SET_1_LONGER()                                                  \
    do {                                                                \
        if (curNums1Size < curNums2Size) {                              \
            tmp_ptr = curStart1;                                        \
            curStart1 = curStart2;                                      \
            curStart2 = tmp_ptr;                                        \
            tmp = curNums1Size;                                         \
            curNums1Size = curNums2Size;                                \
            curNums2Size = tmp;                                         \
            tmp = i;                                                    \
            i = j;                                                      \
            j = tmp;                                                    \
        }                                                               \
    } while(0)

    remain = curNums1Size + curNums2Size;
    kth_min = remain / 2 + remain % 2;

    do {
        SET_1_LONGER();

        half_of_k = kth_min / 2;
        i = (half_of_k < curNums1Size ? half_of_k : curNums1Size) - 1;
        j = (half_of_k < curNums2Size ? half_of_k : curNums2Size) - 1;

        if (curNums2Size <= 0) {
            goto ONE_IS_EXHAUSTED;
        }

        if (curStart1[i] < curStart2[j]) {
            curStart1 += i + 1;
            curNums1Size -= i + 1;
            kth_min -= i + 1;
            i = 0;
        } else {
            curStart2 += j + 1;
            curNums2Size -= j + 1;
            kth_min -= j + 1;
            j = 0;
        }
    } while(kth_min > 1);

    SET_1_LONGER();

    if (curNums2Size <= 0) {
        goto ONE_IS_EXHAUSTED;
    }

    if (curStart1[i] < curStart2[j]) {
        result = curStart1[i];
        if (curNums1Size == 1) {
            candidate1 = candidate2 = curStart2[j];
        } else {
            candidate1 = curStart1[i + 1];
            candidate2 = curStart2[j];
        }
    } else {
        result = curStart2[j];
        if (curNums2Size == 1) {
            candidate1 = candidate2 = curStart1[i];
        } else {
            candidate1 = curStart1[i];
            candidate2 = curStart2[j + 1];
        }
    }

    if ((nums1Size + nums2Size) % 2 == 0) {
        result = (result + (candidate1 < candidate2 ? candidate1 : candidate2)) / 2;
    }

    return result;

ONE_IS_EXHAUSTED:
    result = curStart1[kth_min - 1];
    if ((nums1Size + nums2Size) % 2 == 0) {
        result = (result + curStart1[kth_min]) / 2;
    }
    return result;
}

int main(int argc, char **argv) {
    int a[] = {1, 3};
    int b[] = {2};

    printf("%f", findMedianSortedArrays1(a, 0, b, 1));
}
