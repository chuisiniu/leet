#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char *s) {
    int start = 0;
    int end = 1;
    int length = 1;
    int max_length = length;

    int i;
    int found;

    if (s[0] == '\0') {
        return 0;
    }

    while (s[end] != '\0') {
        found = 0;
        for (i = start; i < end; i++) {
            if (s[end] == s[i]) {
                start = i + 1;
                length = end - start + 1;
                found = 1;
                break;
            }
        }

        if (!found) {
            length += 1;
            if (length > max_length) {
                max_length = length;
            }
        }

        end += 1;
    }

    return max_length;
}

int lengthOfLongestSubstring1(char *s) {
    unsigned char *start = s;
    unsigned char *end = s + 1;
    int length = 1;
    int max_length = length;
    unsigned char bit_map[16];
    unsigned char *tmp;

    unsigned char arr_pos;
    unsigned char bit;

    if (*start == '\0') {
        return 0;
    }

    bzero(bit_map, sizeof(bit_map));
    bit_map[*start / 8] |= (1 << (*start % 8));

    while (*end != '\0') {
        arr_pos = *end >> 3;
        bit = 1 << (*end & 7);
        if (bit_map[arr_pos] & bit) {
            if (length > max_length) {
                max_length = length;
            }
            for (tmp = start; *tmp != *end; tmp++) {
                bit_map[*tmp >> 3] &= ~(1 << (*tmp & 7));
            }
            start = tmp + 1;
            length = end - start + 1;
        } else {
            length += 1;
            bit_map[arr_pos] |= bit;
        }

        end += 1;
    }

    // 整个字符串都没重复
    if (length > max_length) {
        return length;
    }

    return max_length;
}

int lengthOfLongestSubstring2(char *s) {
    int position_of_char[128];
    int cur;
    int start;
    int max_length = 0;
    int tmp;

    bzero(position_of_char, sizeof(position_of_char));

    for (start = 0, cur = 0; s[cur] != '\0'; cur++) {
        if (position_of_char[s[cur]] >= start) {
            tmp = cur - start;
            if (tmp > max_length) {
                max_length = tmp;
            }
            start = position_of_char[s[cur]] + 1;
        }
        position_of_char[s[cur]] = cur;
    }

    tmp = cur - start;
    if (tmp > max_length) {
        return tmp;
    }

    return max_length;
}

int main(int argc, char **argv) {
    char *str = "au";

    printf("%d\n", lengthOfLongestSubstring2(str));
}
