/*
 * 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。
 * 函数 myAtoi(string s) 的算法如下：
 * 读入字符串并丢弃无用的前导空格
 * 检查第一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
 * 读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
 * 将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
 * 如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
 * 返回整数作为最终结果。
 * 注意：
 *     本题中的空白字符只包括空格字符 ' ' 。
 *     除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
 * 示例 1：
 *     输入：s = "42"
 *     输出：42
 *     解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
 *     第 1 步："42"（当前没有读入字符，因为没有前导空格）
 *             ^
 *     第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 *              ^
 *     第 3 步："42"（读入 "42"）
 *                ^
 *     解析得到整数 42 。
 *     由于 "42" 在范围 [-231, 231 - 1] 内，最终结果为 42 。
 * 示例 2：
 *     输入：s = "   -42"
 *     输出：-42
 *     解释：
 *     第 1 步："   -42"（读入前导空格，但忽视掉）
 *                 ^
 *     第 2 步："   -42"（读入 '-' 字符，所以结果应该是负数）
 *                  ^
 *     第 3 步："   -42"（读入 "42"）
 *                    ^
 *     解析得到整数 -42 。
 *     由于 "-42" 在范围 [-231, 231 - 1] 内，最终结果为 -42 。
 * 示例 3：
 *     输入：s = "4193 with words"
 *     输出：4193
 *     解释：
 *     第 1 步："4193 with words"（当前没有读入字符，因为没有前导空格）
 *              ^
 *     第 2 步："4193 with words"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 *              ^
 *     第 3 步："4193 with words"（读入 "4193"；由于下一个字符不是一个数字，所以读入停止）
 *                  ^
 *     解析得到整数 4193 。
 *     由于 "4193" 在范围 [-231, 231 - 1] 内，最终结果为 4193 。
 * 示例 4：
 *     输入：s = "words and 987"
 *     输出：0
 *     解释：
 *     第 1 步："words and 987"（当前没有读入字符，因为没有前导空格）
 *              ^
 *     第 2 步："words and 987"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 *              ^
 *     第 3 步："words and 987"（由于当前字符 'w' 不是一个数字，所以读入停止）
 *              ^
 *     解析得到整数 0 ，因为没有读入任何数字。
 *     由于 0 在范围 [-231, 231 - 1] 内，最终结果为 0 。
 * 示例 5：
 *     输入：s = "-91283472332"
 *     输出：-2147483648
 *     解释：
 *     第 1 步："-91283472332"（当前没有读入字符，因为没有前导空格）
 *              ^
 *     第 2 步："-91283472332"（读入 '-' 字符，所以结果应该是负数）
 *               ^
 *     第 3 步："-91283472332"（读入 "91283472332"）
 *                          ^
 *     解析得到整数 -91283472332 。
 *     由于 -91283472332 小于范围 [-231, 231 - 1] 的下界，最终结果被截断为 -231 = -2147483648 。
 * 提示：
 *     0 <= s.length <= 200
 *     s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成
 */

int myAtoi(char *s) {
    int res = 0;
    int flag;
    char *tmp = s;
    int max = 0x7FFFFFFF;
    int min = 0x80000000;
    int m;
    int n;

    while (*tmp == ' ' || *tmp == '\t') {
        tmp++;
    }
    flag = *tmp == '-' ? -1 : 1;
    tmp = *tmp == '-' || *tmp == '+' ? tmp + 1 : tmp;
    m = flag > 0 ? max / 10 : -(min / 10);
    n = flag > 0 ? max % 10 : -(min % 10);

    if (*tmp < '0' || *tmp > '9') {
        return 0;
    }

    for (; *tmp > '0' - 1 && *tmp < '9' + 1; tmp++) {
        if ((res == m && *tmp - '0' >= n) || res > m) {
            return flag > 0 ? max : min;
        }
        res *= 10;
        res += *tmp - '0';
    }

    return res * flag;
}

int myAtoi1(char *s) {
    enum State {
        START = 0,
        SIGNED,
        IN_NUMBER,
        END,
        STATE_MAX
    };
    enum Input {
        SPACE = 0,
        SIGN,
        NUMBER,
        OTHER,
        INPUT_MAX
    };
    int table[STATE_MAX][INPUT_MAX] = {
        [START]     = {
            [SPACE]  = START,
            [SIGN]   = SIGNED,
            [NUMBER] = IN_NUMBER,
            [OTHER]  = END,
        },
        [SIGNED]    = {
            [SPACE]  = END,
            [SIGN]   = END,
            [NUMBER] = IN_NUMBER,
            [OTHER]  = END,
        },
        [IN_NUMBER] = {
            [SPACE]  = END,
            [SIGN]   = END,
            [NUMBER] = IN_NUMBER,
            [OTHER]  = END,
        },
        [END]       = {
            [SPACE]  = END,
            [SIGN]   = END,
            [NUMBER] = END,
            [OTHER]  = END,
        }
    };
    enum Input input;
    enum State state = START;
    char c;
    int i = 0;

    int result = 0;
    int sign = 1;
    int max = 0x7FFFFFFF;
    int min = 0x80000000;
    int m;
    int n;

    if (s[0] == 0) {
        return 0;
    }

#define INPUT()                                 \
    do {                                        \
        c = s[i];                               \
        if (c == ' ' || c == '\t')              \
            input = SPACE;                      \
        else if (c == '+' || c == '-')          \
            input = SIGN;                       \
        else if (c >= '0' && c <= '9')          \
            input = NUMBER;                     \
        else                                    \
            input = OTHER;                      \
        i++;                                    \
    } while(0)

#define UPDATE_STATE() \
    do {               \
        state = table[state][input];            \
    } while(0)

    m = max / 10;
    n = max % 10;
    do {
        INPUT();
        UPDATE_STATE();

        switch (state) {
        case START:
            break;
        case SIGNED:
            if (c == '-') {
                sign = -1;
                m = -(min / 10);
                n = -(min % 10);
            }
            break;
        case IN_NUMBER:
            if ((result == m && c - '0' >= n) || result > m) {
                return sign == 1 ? max : min;
            }
            result *= 10;
            result += c - '0';
          break;
        case END:
            return result * sign;
        default:
            break;
        }
    } while (state != END);

    return 0;
}
