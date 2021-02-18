/*
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持
 * '.' 和 '*' 的正则表达式匹配。
 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 * 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 * 示例 1：
 *     输入：s = "aa" p = "a"
 *     输出：false
 *     解释："a" 无法匹配 "aa" 整个字符串。
 * 示例 2:
 *     输入：s = "aa" p = "a*"
 *     输出：true
 *     解释：因为 '*'代表可以匹配零个或多个前面的那一个元素,在这里前面的元素就是
 *     'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
 * 示例 3：
 *     输入：s = "ab" p = ".*"
 *     输出：true
 *     解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
 * 示例 4：
 *     输入：s = "aab" p = "c*a*b"
 *     输出：true
 *     解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a'
 *     被重复一次。因此可以匹配字符串 "aab"。
 * 示例 5：
 *     输入：s = "mississippi" p = "mis*is*p*."
 *     输出：false
 * 提示：
 *     0 <= s.length <= 20
 *     0 <= p.length <= 30
 *     s 可能为空，且只包含从 a-z 的小写字母。
 *     p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
 *     保证每次出现字符 * 时，前面都匹配到有效的字符
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 48

struct StarState {
    char c; // 要匹配的字符
    int star_position; // '*'在p中的位置
    int position_in_s;    // '*'在s中匹配的位置
    int cost; // '*' 消耗了几个字符
};

struct StateStack {
    int top;
    struct StarState stack[MAX_STACK_SIZE];
};

static inline void stack_init(struct StateStack *ss) { ss->top = -1; }

static inline int stack_is_empty(struct StateStack *ss) { return ss->top == -1; }

static inline int stack_push(struct StateStack *ss, char c, int position_in_s,
                             int star_position, int cost) {
    if (ss->top == MAX_STACK_SIZE - 1) {
        return 0;
    }

    ss->top += 1;
    ss->stack[ss->top].c = c;
    ss->stack[ss->top].star_position = star_position;
    ss->stack[ss->top].position_in_s = position_in_s;
    ss->stack[ss->top].cost = cost;

    return 1;
}

static inline struct StarState *stack_pop(struct StateStack *ss) {
    return -1 == ss->top ? (struct StarState *)0 : &ss->stack[ss->top--];
}

int isMatch(char *s, char *p) {
    struct StateStack ss;
    int s_position;
    int p_position;
    int cost;
    char c;

    struct StarState *tmp;
    int next_char;
    int mismatch;

    if (s[0] == 0 && p[0] == 0) {
        return 1;
    }

    s_position = 0;
    p_position = 0;
    stack_init(&ss);

    while (1) {
        next_char = p_position + 1;

        // p_position后面的如a*b*c*连续*匹配压入栈
        while (p[p_position] != '\0' && p[next_char] == '*') {
            // x***** 看作x*
            while (p[next_char + 1] == '*') {
                next_char += 1;
            }

            stack_push(&ss, p[p_position], s_position, next_char, 0);
            p_position = next_char + 1;
            next_char = p_position + 1;
        }

        // printf("%s %s %d\n", s + s_position, p + p_position, ss.top + 1);

        // 开始正常值的匹配
        if (s[s_position] == '\0' && p[p_position] == '\0') {
            return 1;
        }

        if (p[p_position] == s[s_position]
            || (s[s_position] != '\0' && p[p_position] == '.')) {
            p_position++;
            s_position++;
            continue;
        }

        // 正常值没匹配中且栈中没有*可以消耗字符
        if (stack_is_empty(&ss)) {
            return 0;
        }

        tmp = stack_pop(&ss);
        if (s[tmp->position_in_s + tmp->cost] == '\0') {
            // 栈顶的*已经把s给消耗完了，出栈就行
            if (p[tmp->star_position + 1] == '\0') {
                return 1;
            }
            continue;
        }

        s_position = tmp->position_in_s + tmp->cost;
        p_position = tmp->star_position + 1;
        if (tmp->c == s[s_position] ||
            (s[s_position] != '\0' && tmp->c == '.')) {
            // 栈顶的*可以消耗一个字符，则多消耗一个字符，重新入栈
            stack_push(&ss, tmp->c, tmp->position_in_s, tmp->star_position,
                       tmp->cost + 1);
            s_position += 1;
        } else if (stack_is_empty(&ss)) {
            break;
        } else {
            // 栈顶*无法消耗字符，则出栈，且把之前消耗的字符恢复回去
            s_position = tmp->position_in_s;
        }
    }

    return s[s_position] == '\0' && p[p_position] == '\0';
}

int isMatch1(char *s, char *p) {
    int i;
    int match;

    if ('\0' == s[0] && '\0' == p[0]) {
        return 1;
    }

    if (p[0] == '\0') {
        return 0;
    }

    if (p[1] == '*') {
        i = -1;
        do {
            i++;
            if (isMatch1(s + i, p + 2)) {
                return 1;
            }
        } while(s[i] == p[0] || (s[i] != '\0' && p[0] == '.'));
    }

    if (s[0] == p[0] || (p[0] == '.' && s[0] != '\0')) {
        return isMatch1(s + 1, p + 1);
    }

    return 0;
}

#define MAX_STR_LEN 48

int isMatch2(char *s, char *p) {
    int state_array[MAX_STR_LEN][MAX_STR_LEN];
    int i;
    int j;
    int k;

    // printf("%s\n%s\n", s, p);

    if (p[0] == '\0') {
        return s[0] == '\0';
    }

    /* state_array[i][j] 表示s的前i个元素和p的前j个元素匹配 */
    for (i = 0; i < MAX_STR_LEN; i++) {
        for (j = 0; j < MAX_STR_LEN; j++) {
            state_array[i][j] = 0;
        }
    }
    state_array[0][0] = 1;

    for (i = 0; i== 0 || s[i - 1] != '\0'; i++) {
        for (j = 1; p[j - 1] != '\0'; j++) {
            if (p[j - 1] == '*') {
                if (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
                    state_array[i][j] = state_array[i][j - 2]
                        || state_array[i - 1][j - 2] || state_array[i - 1][j];
                } else {
                    state_array[i][j] = state_array[i][j - 2];
                }
            } else {
                if (i > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
                    state_array[i][j] = state_array[i - 1][j - 1];
                }
            }
            // printf("%d %d %d\n", i, j, state_array[i][j]);
        }
    }

    return state_array[i - 1][j - 1];
}

int main(int argc, char **argv) {
    printf("0 %d\n", isMatch2("ab", ".*c"));
    printf("1 %d\n", isMatch2("aab", "c*a*b"));
    printf("1 %d\n", isMatch2("ab", ".*"));
    printf("0 %d\n", isMatch2("a", ".*..a*"));
    printf("1 %d\n", isMatch2("", ".*"));
    printf("0 %d\n", isMatch2("b", "c*bb"));
    printf("0 %d\n", isMatch2("ccbbabbbabababa", ".*.ba*c*c*aab.a*b*"));
    printf("1 %d\n", isMatch2("aaa", "ab*a*c*a"));
    printf("0 %d\n", isMatch2("aa", "a"));
    printf("1 %d\n", isMatch2("mississippi", "mis*is*ip*."));
    printf("1 %d\n", isMatch2("ab", ".*.."));
    printf("0 %d\n", isMatch2("a", "ab*a"));
    printf("1 %d\n", isMatch2("", ".*"));
    printf("0 %d\n", isMatch2("a", ""));
    printf("0 %d\n", isMatch2("aab", "b.*"));
    printf("0 %d\n", isMatch2("abb", "b*"));
    exit(0);
}
