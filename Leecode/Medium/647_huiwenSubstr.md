#### Description

给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

#### My Solution

Not good solution. No need to do recursion. Slow and occupy much space

```c++
class Solution { 
public:
    int countSubstrings(string s) {
        int ans = 0;
        for(int i = 0; i < s.length(); i++) {
            isHuiwen(s, ans, i, i);
            if(i < s.length() - 1) isHuiwen(s, ans, i, i + 1);
        }
        return ans;
    }
    void isHuiwen(string s, int& num, int head, int rear) {
        if(s[rear] == s[head]) {
            ++num;
            if(head > 0 && rear < s.length() - 1)
                isHuiwen(s, num, head - 1, rear + 1);
        }
    }
};
```

#### Sample Solution

- 枚举每一个可能的回文中心，然后用两个指针分别向左右两边拓展，当两个指针指向的元素相同的时候就拓展，否则停止拓展。时间复杂度 O($n^2$); 空间复杂度 O(1)

  ```c++
  class Solution {
  public:
      int countSubstrings(string s) {
          int n = s.size(), ans = 0;
          for (int i = 0; i < 2 * n - 1; ++i) {
              int l = i / 2, r = i / 2 + i % 2;
              while (l >= 0 && r < n && s[l] == s[r]) {
                  --l;
                  ++r;
                  ++ans;
              }
          }
          return ans;
      }
  };
  ```

- Manacher 算法。时间复杂度：*O*(*n*); 空间复杂度：O(n)

  Manacher 算法是在线性时间内求解最长回文子串的算法。

  Manacher 算法也会面临「方法一」中的奇数长度和偶数长度的问题，它的处理方式是在所有的相邻字符中间插入 \##，比如 abaaabaa 会被处理成 \#a\#b\#a\#a\##a#b#a#a#，这样可以保证所有找到的回文串都是奇数长度的，以任意一个字符为回文中心，既可以包含原来的奇数长度的情况，也可以包含原来偶数长度的情况。假设原字符串为 S，经过这个处理之后的字符串为 s。**(合并了奇偶，便于各个字符为中心的最大回文半径求和就是回文子串个数)**

  我们用 f(i) 来表示以 s 的第 i 位为回文中心，可以拓展出的最大回文半径，那么 f(i) - 1就是以 i 为中心的最大回文串长度 （想一想为什么）。

  ![image-20200819205342727](C:\Users\SURFACE\AppData\Roaming\Typora\typora-user-images\image-20200819205342727.png)

  ```c++
  class Solution {
  public:
      int countSubstrings(string s) {
          int n = s.size();
          string t = "$#";
          for (const char &c: s) {
              t += c;
              t += '#';
          }
          n = t.size();
          t += '!';
  
          auto f = vector <int> (n);
          int iMax = 0, rMax = 0, ans = 0;
          for (int i = 1; i < n; ++i) {
              // 初始化 f[i]
              f[i] = (i <= rMax) ? min(rMax - i + 1, f[2 * iMax - i]) : 1;
              // 中心拓展
              while (t[i + f[i]] == t[i - f[i]]) ++f[i];
              // 动态维护 iMax 和 rMax
              if (i + f[i] - 1 > rMax) {
                  iMax = i;
                  rMax = i + f[i] - 1;
              }
              // 统计答案, 当前贡献为 (f[i] - 1) / 2 上取整
              ans += (f[i] / 2);
          }
  
          return ans;
      }
  };
  ```

  

#### Note

1. 递归用循环代替会更快占更少内存，当代码好写时就循环吧
2. Manacher 算法是在线性时间内求解最长回文子串的算法，巧妙运用在了求回文子串个数。
