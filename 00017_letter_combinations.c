#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct key {
	char num;
	char start;
	char len;
};
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int *returnSize)
{
	static struct key keys[8];
	static int init_ok = 0;
	int i;
	int j;
	int k;
	int l;
	int end;
	int nr_max_str;
	int tmp;
	int len;
	char *buf;
	char **result;
	int nr[5] = {1, 1, 1, 1, 1};
	struct key *key;

	if ('\0' == digits[0]) {
		*returnSize = 0;
		return NULL;
	}

	if (0 == init_ok) {
		init_ok = 1;
		tmp = 'a';
		for (i = 0; i < 8; i++) {
			keys[i].num = '2' + i;
			keys[i].start = tmp;
			if (5 == i || 7 == i) {
				keys[i].len = 4;
			} else {
				keys[i].len = 3;
			}
			tmp += keys[i].len;
		}
	}

	*returnSize = 0;
	len = strlen(digits) - 1;
	nr_max_str = 1;

	for (i = 0; i <= len; i++) {
		for (j = i + 1; j <= len; j++) {
			nr[i] *= keys[digits[j] - '2'].len;
		}
		nr_max_str *= keys[digits[i] - '2'].len;
	}

	buf = malloc(nr_max_str * (sizeof(char *) + len + 2));
	result = (char **)buf;
	buf = (char *)result + nr_max_str * sizeof(char *);

	for (i = 0; i < nr_max_str; i++) {
		result[i] = buf + i * (len + 2);
		result[i][len + 1] = '\0';
	}

	for (i = 0; i < len + 1; i++) {
		key = &keys[digits[i] - '2'];
		end = key->start + key->len;
		tmp = 0;
		while (tmp < nr_max_str) {
			for (j = key->start; j < end; j++) {
				for (k = 0; k < nr[i]; k++) {
					result[tmp++][i] = j;
				}
			}
		}
	}
	*returnSize = nr_max_str;

	return result;
}

int main(int argc, char **argv)
{
	int i;
	int returnSize;
	char **result;

	result = letterCombinations("2397", &returnSize);

	for (i = 0; i < returnSize; i++) {
		printf("%d %s\n", i, result[i]);
	}
}
