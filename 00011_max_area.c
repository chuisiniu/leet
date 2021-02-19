/*
 * 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai)
 * 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)
 * 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 * 说明：你不能倾斜容器。
 * 示例 1：
 *     输入：[1,8,6,2,5,4,8,3,7]
 *     输出：49
 *     解释：图中垂直线代表输入数组[1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 * 示例 2：
 *     输入：height = [1,1]
 *     输出：1
 * 示例 3：
 *     输入：height = [4,3,2,1,4]
 *     输出：16
 * 示例 4：
 *     输入：height = [1,2,1]
 *     输出：2
 * 提示：
 *     n = height.length
 *     2 <= n <= 3 * 104
 *     0 <= height[i] <= 3 * 104
 */
#include <stdio.h>

int maxArea(int *height, int heightSize) {
    int i;
    int j;
    int h;
    int pre;
    int area;
    int max;

    for (i = 0, j = heightSize - 1, pre = 0, max = 0; i < j;) {
        h = height[i] < height[j] ? height[i++] : height[j--];
        if (pre < h) {
            area = h * (j - i + 1);
            max = area > max ? area : max;
            pre = h;
        }
    }

    return max;
}

int main(int argc, char **argv) {
    int test[] = {
        76,  155, 15,  188, 180, 154, 84,  34,  187, 142, 22,  5,   27,  183, 111,
        128, 50,  58,  2,   112, 179, 2,   100, 111, 115, 76,  134, 120, 118, 103,
        31,  146, 58,  198, 134, 38,  104, 170, 25,  92,  112, 199, 49,  140, 135,
        160, 20,  185, 171, 23,  98,  150, 177, 198, 61,  92,  26,  147, 164, 144,
        51,  196, 42,  109, 194, 177, 100, 99,  99,  125, 143, 12,  76,  192, 152,
        11,  152, 124, 197, 123, 147, 95,  73,  124, 45,  86,  168, 24,  34,  133,
        120, 85,  81,  163, 146, 75,  92,  198, 126, 191
    };

    printf("%d\n", maxArea(test, sizeof(test) / sizeof(int)));
}
