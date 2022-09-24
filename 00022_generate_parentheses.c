/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int pow_of_3(unsigned char n)
{
	int i;
	int result;

	result = 1;
	for (i = 0; i < n; i++)
		result *= 3;

	return result;
}

struct counter {
		int nr_left;
		int nr_right;
};

#ifndef NULL
#define NULL ((void *)0)
#endif

char **generateParenthesis(int n, int *returnSize)
{
	struct counter *cntr;
	char **result;
	int max_size;
	int i;
	int j;
	int pre_size;

	max_size = pow_of_3(n - 1);
	result = malloc(max_size * sizeof(int *));
	bzero(result, max_size * sizeof(int *));

	cntr = malloc(max_size * sizeof(struct counter));
	cntr[0].nr_left = n - 1;
	cntr[0].nr_right = 1;
	result[0] = malloc(n * 2 + 1);
	bzero(result[0], 2 * n + 1);
	result[0][0] = '(';
	*returnSize = 1;
	for (i = 1; i < 2 * n; i++) {
		pre_size = *returnSize;
		for (j = 0; j < pre_size; j++) {
			if (cntr[j]. nr_left > 0 && cntr[j].nr_right > 0) {
				result[*returnSize] = malloc(n * 2 + 1);
				bzero(result[*returnSize], 2 * n + 1);
				result[j][i] = '(';

				memcpy(result[*returnSize], result[j], i);
				result[*returnSize][i] = ')';

				cntr[*returnSize].nr_left = cntr[j].nr_left;
				cntr[*returnSize].nr_right = cntr[j].nr_right - 1;
				cntr[j].nr_left -= 1;
				cntr[j].nr_right += 1;

				*returnSize += 1;
			} else if (cntr[j].nr_left > 0) {
				result[j][i] = '(';
				cntr[j].nr_left -= 1;
				cntr[j].nr_right += 1;
			} else if (cntr[j].nr_right > 0) {
				memset(result[j] + i, ')', cntr[j].nr_right);
				cntr[j].nr_right = 0;
			} else
				continue;
		}
	}

	free(cntr);

	return result;
}

int main(int argc, char **argv)
{
	char **result;
	int size;
	int n;
	int i;

	n = 3;
	if (2 == argc) {
		n = atoi(argv[1]);

		if (n > 8 || n < 1) {
			printf("invalid arg %s\n", argv[1]);

			exit(-1);
		}
	}

	result = generateParenthesis(n, &size);

	for (i = 0; i < size; i++) {
		printf("%s\n", result[i]);
		free(result[i]);
	}

	free(result);

	exit(0);
}
