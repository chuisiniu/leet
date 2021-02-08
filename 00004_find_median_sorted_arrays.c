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

/* findMedianSortedArrays1 使用二分法排除数组前面不可能是中位数的
 * 数组成员。设两个数组的剩余的个数为remain，中位数是第k小的数kth_min
 * 那么两个数组中第kth_min / 2个成员较小的前面的成员不可能是中位数
 */
double findMedianSortedArrays1(int *nums1, int nums1Size,
                               int *nums2, int nums2Size) {
    int is_odd;
    int remain;
    int kth_min;
    int half_of_k;

    int i;
    int j;
    int *tmp_ptr;
    int tmp;

    if (1 == nums1Size && 1 == nums2Size) {
        return (double)(nums1[0] + nums2[0]) / 2;
    }

    remain = nums1Size + nums2Size;
    is_odd = remain % 2;
    kth_min = remain / 2 + is_odd;

#define SET_1_LONGER()                         \
    do {                                       \
        if (nums1Size < nums2Size) {           \
            tmp_ptr = nums1;                   \
            nums1 = nums2;                     \
            nums2 = tmp_ptr;                   \
            tmp = nums1Size;                   \
            nums1Size = nums2Size;             \
            nums2Size = tmp;                   \
            tmp = i;                           \
            i = j;                             \
            j = tmp;                           \
        }                                      \
    } while(0)

    do {
        if (nums2Size <= 0 || nums1Size <= 0) {
            goto ONE_IS_EXHAUSTED;
        }

        half_of_k = kth_min / 2;
        i = (half_of_k < nums1Size ? half_of_k : nums1Size) - 1;
        j = (half_of_k < nums2Size ? half_of_k : nums2Size) - 1;

        // 排除掉nums1[i]和nums2[j]前面的数据
        if (nums1[i] < nums2[j]) {
            i++;
            nums1 += i;
            nums1Size -= i;
            kth_min -= i;
            i = 0;
        } else {
            j++;
            nums2 += j;
            nums2Size -= j;
            kth_min -= j;
            j = 0;
        }
    } while(kth_min > 1);

    if (nums1Size <= 0 || nums2Size <= 0) {
        goto ONE_IS_EXHAUSTED;
    }

    SET_1_LONGER();
    if (nums1[i] < nums2[j]) {
        if (is_odd) {
            return nums1[i];
        }

        if (nums1Size == 1) {
            return (double)(nums1[i] + nums2[j]) / 2;
        } else {
            return (double)(nums1[i] +
                            (nums1[i + 1] < nums2[j] ? nums1[i + 1]
                                                     : nums2[j])
                ) / 2;
        }
    } else {
        if (is_odd) {
            return nums2[j];
        }

        if (nums2Size == 1) {
            return (double)(nums2[j] + nums1[i]) / 2;
        } else {
            return (double)(nums2[j] +
                            (nums1[i] < nums2[j + 1] ? nums1[i]
                                                     : nums2[j + 1])
                            ) / 2;
        }
    }

ONE_IS_EXHAUSTED:
    SET_1_LONGER();

    return is_odd ? nums1[kth_min - 1]
                  : (double)(nums1[kth_min - 1] + nums1[kth_min]) / 2;
}

int main(int argc, char **argv) {
    int a[] = {1, 3};
    int b[] = {2, 3};

    printf("%f", findMedianSortedArrays1(a, 1, b, 2));
}
