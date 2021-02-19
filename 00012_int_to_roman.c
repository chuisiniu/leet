/*
 * 罗马数字包含以下七种字符：I，V，X，L，C，D和M。
 * 字符          数值
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 *
 * 例如， 罗马数字 2 写做 II，即为两个并列的 1。12 写做 XII，即为X+II。 27
 * 写做XXVII, 即为XX+V+II。
 *
 * 通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4
 * 不写做 IIII，而是IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1
 * 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
 *
 * I可以放在V(5) 和X(10) 的左边，来表示 4 和 9。
 * X可以放在L(50) 和C(100) 的左边，来表示 40 和 90。
 * C可以放在D(500) 和M(1000) 的左边，来表示400 和900。
 * 给定一个整数，将其转为罗马数字。输入确保在 1到 3999 的范围内。
 *
 * 示例 1:
 *     输入: 3
 *     输出: "III"
 * 示例 2:
 *     输入: 4
 *     输出: "IV"
 * 示例 3:
 *     输入: 9
 *     输出: "IX"
 * 示例 4:
 *     输入: 58
 *     输出: "LVIII"
 *     解释: L = 50, V = 5, III = 3.
 * 示例 5:
 *     输入: 1994
 *     输出: "MCMXCIV"
 *     解释: M = 1000, CM = 900, XC = 90, IV = 4.
 * 提示：
 *     1 <= num <= 3999
 */

char *intToRoman(int num) {
    struct Roman {
        char c;
        int value;
        struct Roman *unit;
    };
    struct Roman i = {'I', 1, &i};
    struct Roman v = {'V', 5, &i};
    struct Roman x = {'X', 10, &i};
    struct Roman l = {'L', 50, &x};
    struct Roman c = {'C', 100, &x};
    struct Roman d = {'D', 500, &c};
    struct Roman m = {'M', 1000, &c};
    struct Roman *all[] = {&m, &d, &c, &l, &x, &v, &i};
    int j;
    int k;
    int tmp;
    int size;
    int quotient;
    int remainder;

    static char result[128];

    for (j = 0, k = 0, remainder = num;
         remainder != 0 && j < sizeof(all) / sizeof(struct Roman *);
         j++) {
        quotient = remainder / all[j]->value;
        remainder = remainder % all[j]->value;

        for (tmp = 0; tmp < quotient; tmp++) {
            result[k++] = all[j]->c;
        }

        tmp = all[j]->value - all[j]->unit->value;
        if (j != (sizeof(all) / sizeof(struct Roman *) - 1) &&
            remainder >= tmp &&
            remainder < all[j]->value) {
            result[k++] = all[j]->unit->c;
            result[k++] = all[j]->c;

            remainder -= tmp;
        }
    }

    result[k] = '\0';

    return result;
}
