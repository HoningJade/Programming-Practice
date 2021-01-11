#### Description

You are given two strings A and B. Your aim is form string A by concatenating multiple copies of string B. However, before concatenating a copy of string B, you can remove any number of characters from it.

For example,

A = ‘ZAZA’ , length n
B = ‘BAZ’, length m

You can form string by concatenating three copies of string B as follows: ‘##Z’ + ‘#AZ’ + ‘#A#’.(# denotes the characters removed from string B).

Question1. Is it possible to form string A in this way?
Question2. If possible, what is the minimum copies of B required?



#### Solution

Time complexity: O($$m^2$$n)

```c++
#include <string>
#include <limits>

using namespace std;

int minCopy(string s1, string s2) {
    int len = s1.length();
    int memo[len];
    if (s2.find(s1[0]))
        memo[0] = 1;
    else
        memo[0] = 0;
    for (int j = 1; j < len; j++) {  // update memo
        int tempMin = numeric_limits<int>::max() / 2;  // result
        for (int m = 0; m <= j; m++) {  // check [m...j] 0< m < j
            if (m == 0 || memo[m - 1] > 0) {
                int id1 = m, id2 = 0;
                while (id1 <= j || id2 < s2.length()) {
                    if (s1[id1] == s2[id2]) {
                        id1++;
                        id2++;
                    } else
                        id2++;
                }
                if (id1 == j)
                    tempMin = m == 0 ? min(1, tempMin) : min(memo[m - 1], tempMin);
            }
        }
    }
    return memo[len];
}
```



#### Note

1. Dynamic Programming: f(i) = min{f(i), f(j) + 1}, A[j...i] match from str2
2. Key is the O(m) method to decide whether a substring of str1 can be matched form str2. Don’t generate every possible strings from str2.

