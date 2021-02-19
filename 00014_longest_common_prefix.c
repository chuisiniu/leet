/*
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * 如果不存在公共前缀，返回空字符串 ""。
 * 示例 1：
 *     输入：strs = ["flower","flow","flight"]
 *     输出："fl"
 * 示例 2：
 *     输入：strs = ["dog","racecar","car"]
 *     输出：""
 *     解释：输入不存在公共前缀。
 * 提示：
 *     0 <= strs.length <= 200
 *     0 <= strs[i].length <= 200
 *     strs[i] 仅由小写英文字母组成
 */

#define MAX_STR_LEN 256


char *longestCommonPrefix(char **strs, int strsSize) {
    static char result[MAX_STR_LEN];
    int i;
    int j;
    int k;
    char c;

    k = 0;
    if (strsSize == 0) {
        goto END;
    }

    i = 0;
    while (1) {
        if ('\0' == (c = strs[0][i])) {
            goto END;
        }
        for (j = 1; j < strsSize; j++) {
            if (strs[j][i] != c) {
                goto END;
            }
        }
        result[k++] = c;
        i++;
    }

END:
    result[k] = '\0';

    return result;
}
