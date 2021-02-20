/*
 * 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c
 * ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。
 * 注意：答案中不可以包含重复的三元组。
 * 示例 1：
 *     输入：nums = [-1,0,1,2,-1,-4]
 *     输出：[[-1,-1,2],[-1,0,1]]
 * 示例 2：
 *     输入：nums = []
 *     输出：[]
 * 示例 3：
 *     输入：nums = [0]
 *     输出：[]
 * 提示：
 *     0 <= nums.length <= 3000
 *     -105 <= nums[i] <= 105
 */
#include <stdio.h>
#include <stdlib.h>

void print(int *nums, int numsSize) {
    int i;

    for (i = 0; i < numsSize; i++) {
        if (i < numsSize - 1) {
            printf("%d ", nums[i]);
        } else {
            printf("%d", nums[i]);
        }
    }
    printf("\n");
}

#define MAX_NUMS_SIZE 4096

void quick_sort(int *nums, int numsSize) {
    int flag;
    int i;
    int j;

    if (numsSize <= 1) {
        return;
    }

    i = 0;
    j = numsSize - 1;
    flag = nums[i];
    while (i < j) {
        for (;j > i && nums[j] >= flag; j--);
        if (i < j) {
            nums[i] = nums[j];
        }

        for (;j > i && nums[i] <= flag; i++);
        if (i < j) {
            nums[j] = nums[i];
        }
    }

    nums[i] = flag;

    quick_sort(nums, i);
    quick_sort(nums + i + 1, numsSize - i - 1);
}

int bifind(int *nums, int numsSize, int target) {
    int mid;
    int tmp;

    if (numsSize < 1) {
        return -1;
    }

    mid = numsSize / 2;
    if (nums[mid] == target) {
        return mid;
    }

    if (nums[mid] > target) {
        return bifind(nums, mid, target);
    }

    if (-1 == (tmp = bifind(nums + mid + 1, numsSize - mid - 1, target))) {
        return -1;
    }
    return mid + 1 + tmp;
}

#define MAX_MALLOC_SIZE 81920

/* 要保证a <= b <= c */
void add_result(int **result, int *returnColumnSizes, int *resultSize,
                int a, int b, int c) {
    result[*resultSize] = malloc(3 * sizeof(int));

    result[*resultSize][0] = a;
    result[*resultSize][1] = b;
    result[*resultSize][2] = c;

    returnColumnSizes[*resultSize] = 3;

    *resultSize += 1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize,
               int **returnColumnSizes) {
    int i;
    int j;
    int m;
    int tmp;

    int start;
    int end;

    int **result;
    long long malloc_size;

    *returnSize = 0;
    *returnColumnSizes = 0;
    if (numsSize < 3) {
        return 0;
    }

    quick_sort(nums, numsSize);

    malloc_size = (long long)numsSize * (numsSize - 1) * (numsSize - 2) / 6;
    malloc_size = malloc_size < MAX_MALLOC_SIZE ? malloc_size : MAX_MALLOC_SIZE;
    result = malloc(malloc_size * sizeof(int *));
    *returnColumnSizes = malloc(malloc_size * sizeof(int));
    for (i = 0; i < malloc_size; i++) {
        result[i] = 0;
        (*returnColumnSizes)[i] = 0;
    }

    i = 0;
    j = numsSize - 1;
    while (i < numsSize && j >= 0 && nums[i] < 0 && nums[j] > 0) {
        if (-nums[i] >= nums[j]) {
            // - + +   - 0 +
            start = i;
            for (m = j; nums[m] > 0;) {
                tmp = 0 - nums[i] - nums[m];
                if (tmp <= nums[m] && -1 != (tmp = bifind(nums + start, m - start, tmp))) {
                    add_result(result, *returnColumnSizes, returnSize,
                               nums[i], nums[start + tmp], nums[m]);
                    start = tmp + 1;
                }

                tmp = nums[m--];
                while (nums[m] > 0 && tmp == nums[m]) {
                    m--;
                }
            }

            tmp = nums[i++];
            while (i < numsSize && tmp == nums[i]) {
                i++;
            }
        } else {
            // - - +
            end = j;
            for (m = i; nums[m] < 0;) {
                tmp = 0 - nums[j] - nums[m];
                if (tmp >= nums[m] && -1 != (tmp = bifind(nums + m + 1, end - m, tmp))) {
                    add_result(result, *returnColumnSizes, returnSize,
                               nums[m + 1 + tmp], nums[m], nums[j]);
                    end = m + 1 + tmp - 1;
                }

                tmp = nums[m++];
                while (nums[m] < 0 && tmp == nums[m]) {
                    m++;
                }
            }
            tmp = nums[j--];
            while (nums[j] > 0 && tmp == nums[j]) {
                j--;
            }
        }
    }

    if (j - i > 1
        && (nums[i] == 0 && nums[i + 1] == 0 && nums[i + 2] == 0
            || nums[j] == 0 && nums[j - 1] == 0 && nums[j - 2] == 0)) {
        add_result(result, *returnColumnSizes, returnSize, 0, 0, 0);
    }

    return result;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **threeSum1(int *nums, int numsSize, int *returnSize,
               int **returnColumnSizes) {
    int i;
    int sum;
    int tmp;

    int start;
    int end;

    int **result;
    long long malloc_size;

    *returnSize = 0;
    *returnColumnSizes = 0;
    if (numsSize < 3) {
        return 0;
    }

    quick_sort(nums, numsSize);

    malloc_size = (long long)numsSize * (numsSize - 1) * (numsSize - 2) / 6;
    malloc_size = malloc_size < MAX_MALLOC_SIZE ? malloc_size : MAX_MALLOC_SIZE;
    result = malloc(malloc_size * sizeof(int *));
    *returnColumnSizes = malloc(malloc_size * sizeof(int));
    for (i = 0; i < malloc_size; i++) {
        result[i] = 0;
        (*returnColumnSizes)[i] = 0;
    }

    for (i = 0; i < numsSize && nums[i] <= 0;) {
        start = i + 1;
        end = numsSize - 1;
        while (start < end) {
            sum = nums[i] + nums[start] + nums[end];
            if (sum == 0) {
                add_result(result, *returnColumnSizes, returnSize,
                           nums[i], nums[start], nums[end]);
                for (tmp = nums[start]; start < end && tmp == nums[++start];) {}
                for (tmp = nums[end]; start < end && tmp == nums[--end];) {}
            } else if (sum < 0) {
                start++;
            } else {
                end--;
            }
        }
        for (tmp = nums[i]; i < numsSize && tmp == nums[i];) {i++;}
    }

    return result;
}

int main(int argc, char **argv) {
    int nums[] = {1, 3, -2, 4, 0, -8, 9};
    int numsSize = sizeof(nums) / sizeof(int);
    print(nums, numsSize);
    quick_sort(nums, numsSize);
    print(nums, numsSize);

    exit(0);
}
