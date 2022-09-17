/*
 * 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足
 * 下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]]（若两个四元
 * 组元素一一对应，则认为两个四元组重复）：
 *
 *     0 <= a, b, c, d < n
 *     a、b、c 和 d 互不相同
 *     nums[a] + nums[b] + nums[c] + nums[d] == target
 * 你可以按 任意顺序 返回答案 。
 *
 * 示例 1：
 *
 * 输入：nums = [1,0,-1,0,-2,2], target = 0
 * 输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 * 示例 2：
 *
 * 输入：nums = [2,2,2,2,2], target = 8
 * 输出：[[2,2,2,2]]
 *
 * 提示：
 *
 * 1 <= nums.length <= 200
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 */

#include <stdlib.h>
#include <stdio.h>

int cmp(const void *d1, const void *d2) { return *((int *)d1) - *((int *)d2); }

int binary_search(int *nums, int start, int end, long long target)
{
	int s;
	int e;
	int m;

	s = start;
	e = end;
	while (s <= e) {
		m = (s + e) / 2;

		if (nums[m] == target)
			goto FOUND;
		else if (nums[m] < target)
			s = m + 1;
		else
			e = m - 1;
	}

	return -1;

 FOUND:
	while (m > start + 1)
		if (nums[m - 1] == target)
			m--;
		else
			break;

	return m;
}

void two_sum(int *nums, int start, int end, long long target,
			 int a, int b, int *returnSize, int **array,
			 int *returnColumnSize)
{
	int c;
	int e;
	int d;
	long long sum2;

	c = start;
	e = end;

	while (c < e) {
		if (e - c > 32) {
			sum2 = ((long long)nums[c]) + nums[c + 1];
			if (sum2 == target) {
				d = c + 1;
				goto FOUND;
			} else if (sum2 > target)
				goto NEXT;
			sum2 = ((long long)nums[c]) + nums[e];
			if (sum2 == target) {
				d = e;
				goto FOUND;
			} else if (sum2 < target)
				goto NEXT;
		}
		d = binary_search(nums, c + 1, e, target - nums[c]);
	FOUND:
		if (d > 0) {
			array[*returnSize] = malloc(sizeof(int) * 4);
			array[*returnSize][0] = nums[a];
			array[*returnSize][1] = nums[b];
			array[*returnSize][2] = nums[c];
			array[*returnSize][3] = nums[d];
			returnColumnSize[*returnSize] = 4;

			(*returnSize)++;

			e = d - 1;
		}
	NEXT:
		while (c < e - 1)
			if (nums[c] == nums[c + 1])
				c++;
			else
				break;
		c++;
	}
}

void three_sum(int *nums, int start, int end, long long target,
			   int a, int *returnSize, int **array,
			   int *returnColumnSize)
{
	int b;

	b = start;
	while (b < end - 1) {
		if (((long long)nums[b]) + nums[b + 1] + nums[b + 2] > target)
			goto NEXT;
		if (((long long)nums[b]) + nums[end - 1] + nums[end] < target)
			goto NEXT;
		two_sum(nums, b + 1, end, target - nums[b], a, b, returnSize, array,
				returnColumnSize);
	NEXT:
          while (b < end - 1)
			if (nums[b] == nums[b + 1])
				b++;
			else
				break;
		b++;
	}
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 * assume caller calls free().
 */
int **fourSum(int *nums, int numsSize, int target, int *returnSize,
              int **returnColumnSizes)
{
	int a;
	int **array;
	int max_a;
	int size;

	if (numsSize < 4) {
		*returnSize = 0;
		*returnColumnSizes = NULL;
		return NULL;
	}

	qsort(nums, numsSize, sizeof(int), cmp);

	size = numsSize * (numsSize - 1) * (numsSize - 2);
	*returnSize = 0;
	array = malloc(sizeof(int *) * size);
	*returnColumnSizes = malloc(sizeof(int) * size);
	max_a = numsSize - 3;

	a = 0;
	while (a < max_a) {
		if (((long long)nums[a]) + nums[a + 1] + nums[a + 2] + nums[a + 3] > target)
			goto NEXT;
		if (((long long)nums[a]) + nums[max_a] + nums[max_a + 1] + nums[max_a + 2] < target)
			goto NEXT;
		three_sum(nums, a + 1, numsSize - 1, ((long long)target) - nums[a], a, returnSize,
				  array, *returnColumnSizes);
	NEXT:
		while (a < max_a)
			if (nums[a] == nums[a + 1])
				a++;
			else
				break;
		a++;
	}

	return array;
}

int main(int argc, char **argv)
{
	int **array;
	int returnSize;
	int *retureColumnSizes;

	int nums[] = {1,0,-1,0,-2,2};
	int target = 0;

	array = fourSum(nums, sizeof(nums) / sizeof(nums[0]), target, &returnSize, &retureColumnSizes);

	exit(0);
}
