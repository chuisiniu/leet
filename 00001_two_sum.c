/*
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值
 * 的那 两个 整数，并返回它们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 *
 * 你可以按任意顺序返回答案。
 *
 * 示例 1：
 *    输入：nums = [2,7,11,15], target = 9
 *    输出：[0,1]
 *    解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
 * 示例 2：
 *    输入：nums = [3,2,4], target = 6
 *    输出：[1,2]
 * 示例 3：
 *    输入：nums = [3,3], target = 6
 *    输出：[0,1]
 */
#include <stdlib.h>
#include <stdio.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int *result = (int *)0;

    if (numsSize < 2) {
        return result;
    }

    *returnSize = 0;
    result = malloc(sizeof(int) * 2);
    for (result[0] = 0; result[0] < numsSize; result[0]++) {
        for (result[1] = result[0] + 1; result[1] < numsSize; result[1]++) {
            if (nums[result[0]] + nums[result[1]] == target) {
                *returnSize = 2;
                return result;
            }
        }
    }

    free(result);
    *returnSize = 0;

    return (int *)0;
}

int *twoSum1(int *nums, int numsSize, int target, int *returnSize) {
    int *result = (int *)0;
    int tmp;

    if (numsSize < 2) {
        return result;
    }

    *returnSize = 0;
    result = malloc(sizeof(int) * 2);
    for (result[0] = 0; result[0] < numsSize; result[0]++) {
        tmp = target - result[0];
        for (result[1] = result[0] + 1; result[1] < numsSize; result[1]++) {
            if (nums[result[1]] == tmp) {
                *returnSize = 2;
                return result;
            }
        }
    }

    free(result);
    *returnSize = 0;

    return (int *)0;
}

int main(int argc, char **argv) {
    int nums[] = {2, 7, 11, 15};
    int *res;
    int res_size;

    res = twoSum(nums, 4, 9, &res_size);

    if (res_size > 0) {
        printf("%d %d\n", res[0], res[1]);
    }

    exit(0);
}
