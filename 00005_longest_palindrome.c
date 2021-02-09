/* 给你一个字符串 s，找到 s 中最长的回文子串。
 *  示例 1：
 *      输入：s = "babad"
 *      输出："bab"
 *      解释："aba" 同样是符合题意的答案。
 *  示例 2：
 *      输入：s = "cbbd"
 *      输出："bb"
 *  示例 3：
 *      输入：s = "a"
 *      输出："a"
 *  示例 4：
 *      输入：s = "ac"
 *      输出："a"
 *
 *  提示：
 *      1 <= s.length <= 1000
 *      s 仅由数字和英文字母（大写和/或小写）组成
 */
#include <stdlib.h>
#include <stdio.h>

char *longestPalindrome(char *s) {
    int i;
    int start;
    int end;
    int len;
    int str_len;
    int max_start;
    int max_end;
    int max_len;

#define CHECK_LOOP(__s__, __e__)                                        \
    do {                                                                \
        for (start = (__s__), end = (__e__),                            \
                 len = ((__s__) == (__e__) ? 1 : 2);                    \
             start >= 0 && s[end] != '\0';                              \
             start--, end++, len += 2) {                                \
            if (s[start] != s[end]) {                                   \
                break;                                                  \
            }                                                           \
        }                                                               \
        if (len > max_len) {                                            \
            max_start = start + 1;                                      \
            max_end = end - 1;                                          \
            max_len = len;                                              \
        }                                                               \
        if (s[end] == '\0') {                                           \
            str_len = end;                                              \
        }                                                               \
    } while (0)

    for (i = 0, max_len = 0; s[i] != '\0'; i++) {
        CHECK_LOOP(i, i);

        if (s[i + 1] != '\0') {
            CHECK_LOOP(i, i + 1);
        }

        if (str_len > 0 && max_len > (str_len / 2)) {
            break;
        }
    }

    s[max_end + 1] = '\0';

    return s + max_start;
}

char *longestPalindrome1(char *s) {
    unsigned char state[1024][1024] = {0};
    int i;
    int j;
    int len;
    int max_i;
    int max_j;
    int found;
    int not_found_count;

    max_i = 0;
    max_j = 0;
    found = 0;
    for (len = 1; s[len - 1] != '\0'; len++) {
        found = 0;
        for (i = 0, j = i + len - 1; s[j] != '\0'; i++, j++) {
            if (s[i] != s[j]) {
                state[i][j] = 0;
            } else if (j - i < 3) {
                state[i][j] = 1;
                if (0 == found) {
                    max_i = i;
                    max_j = j;
                    found = 1;
                    not_found_count = 0;
                }
            } else {
                state[i][j] = state[i + 1][j - 1];
                if (1 == state[i][j] && 0 == found) {
                    max_i = i;
                    max_j = j;
                    found = 1;
                    not_found_count = 0;
                }
            }
        }
        if (not_found_count == 2) {
            break;
        }
        if (0 == found) {
            not_found_count++;
        }
    }

    s[max_j + 1] = 0;

    return s + max_i;
}

/* Manacher 算法 */
char *longestPalindrome2(char *s) {
    int origin_len;
    int tmp_len;
    char tmp[2048];
    int state[2048];

    int center;
    int max_right;
    int mirror;
    int i;
    int j;
    int k;
    int max_ext;
    int max_pos;
    int pos;
    int step;
    int left;
    int right;

    /* 把每个字符使用一个字符串中不存在的值包起来，消除回文中心是一个还是两个的问题 */
    for (origin_len = 0, tmp_len = 0; s[origin_len] != '\0';) {
        state[tmp_len] = 0;
        tmp[tmp_len++] = '#';
        state[tmp_len] = 1;
        tmp[tmp_len++] = s[origin_len++];
    }
    state[tmp_len] = 0;
    tmp[tmp_len++] = '#';
    tmp[tmp_len] = '\0';

    for (i = 0, center = 0, max_right = 0, max_ext = 0; i < tmp_len; i++) {
        /* center为向右扩展最多的回文中心，mirror是i在回文中心左边对称的位置 */
        mirror = center - (i - center);
        if (i < max_right) {
            /* i + state[mirror] 是如果i和mirror情况一样的话向右扩展的最大位置 */
            if (i + state[mirror] < max_right) {
                /* 最大位置在max_right以里，则最大扩展长度就是state[mirror] */
                state[i] = state[mirror];
                continue;
            } else {
                /* 否则i至少可以扩展到max_right - i */
                state[i] = max_right - i;
            }
        }

        /* 回文中心是#的话每比较一个字符则可以多扩展两个位置 */
        step = tmp[i] == '#' ? 2 : 1;
        for (k = state[i] + 1, left = i - k, right = i + k;
             left >= 0 && right < tmp_len && tmp[left] == tmp[right];
             state[i] += step, k = state[i] + 1, left = i - k, right = i + k);

        if (--right > max_right) {
            max_right = right;
            center = i;
        }
        if (state[i] > max_ext) {
            max_pos = ++left;
            max_ext = state[i];
        }
    }

    pos = max_pos / 2 + max_pos % 2;
    s[pos + max_ext] = '\0';

    return s + pos;
}

int main(int argc, char **argv) {
    char s[] = "babadada";

    printf("%s\n", longestPalindrome2(s));

    exit(0);
}
