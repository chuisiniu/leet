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
        while (p[p_position] != '\0' && p[next_char] == '*') {
            while (p[next_char + 1] == '*') {
                next_char += 1;
            }

            stack_push(&ss, p[p_position], s_position, next_char, 0);
            p_position = next_char + 1;
            next_char = p_position + 1;
        }

        // printf("%s %s %d\n", s + s_position, p + p_position, ss.top + 1);
        if (s[s_position] == '\0' && p[p_position] == '\0') {
            return 1;
        }

        if (p[p_position] == s[s_position]
            || (s[s_position] != '\0' && p[p_position] == '.')) {
            p_position++;
            s_position++;
            continue;
        }

        if (stack_is_empty(&ss)) {
            return 0;
        }

        tmp = stack_pop(&ss);
        if (s[tmp->position_in_s + tmp->cost] == '\0') {
            if (p[tmp->star_position + 1] == '\0') {
                return 1;
            }
            continue;
        }

        s_position = tmp->position_in_s + tmp->cost;
        p_position = tmp->star_position + 1;
        if (tmp->c == s[s_position] ||
            (s[s_position] != '\0' && tmp->c == '.')) {
            stack_push(&ss, tmp->c, tmp->position_in_s, tmp->star_position,
                       tmp->cost + 1);
            s_position += 1;
        } else if (stack_is_empty(&ss)) {
            break;
        } else {
            s_position = tmp->position_in_s;
        }
    }

    return s[s_position] == '\0' && p[p_position] == '\0';
}

int main(int argc, char **argv) {
    printf("0 %d\n", isMatch("ab", ".*c"));
    printf("1 %d\n", isMatch("aab", "c*a*b"));
    printf("1 %d\n", isMatch("ab", ".*"));
    printf("0 %d\n", isMatch("a", ".*..a*"));
    printf("1 %d\n", isMatch("", ".*"));
    printf("0 %d\n", isMatch("b", "c*bb"));
    printf("0 %d\n", isMatch("ccbbabbbabababa", ".*.ba*c*c*aab.a*b*"));
    printf("1 %d\n", isMatch("aaa", "ab*a*c*a"));

  exit(0);
}
