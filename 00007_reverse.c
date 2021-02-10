/*
 * 给你一个 32 位的有符号整数 x ，返回 x 中每位上的数字反转后的结果。
 * 如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
 * 假设环境不允许存储 64 位整数（有符号或无符号）。
 * 示例 1：
 *     输入：x = 123
 *     输出：321
 * 示例 2：
 *     输入：x = -123
 *     输出：-321
 * 示例 3：
 *     输入：x = 120
 *     输出：21
 * 示例 4：
 *     输入：x = 0
 *     输出：0
 * 提示：
 *     -2^31 <= x <= 2^31 - 1
 */

int reverse(int x) {
    int rev = 0;
    int pop = 0;

#define INT_MAX 2147483648
#define INT_MIN -2147483647

    while (x != 0) {
        pop = x % 10;
        x /= 10;
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7))
            return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8))
            return 0;
        rev = rev * 10 + pop;
    }
    return rev;
}
