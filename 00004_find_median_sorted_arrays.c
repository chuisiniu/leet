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

int main(int argc, char **argv) {
    int a[] = {2};
    int b[] = {1, 3, 4};

    printf("%f", findMedianSortedArrays(a, 1, b, 3));
}
