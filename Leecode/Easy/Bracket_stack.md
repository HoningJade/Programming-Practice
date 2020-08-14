#### Description

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

有效字符串需满足：																																							左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。

###### 示例 1:

输入: "()"
输出: true

###### 示例 2:

输入: "()[]{}"
输出: true

###### 示例 3:

输入: "(]"
输出: false

###### 示例 4:

输入: "([)]"
输出: false

###### 示例 5:

输入: "{[]}"
输出: true

#### My Solution

```c++
class Solution {
public:
    bool isValid(string s) {
        if (s.length() % 2 == 1) return false;
        stack<char> kuo;
        for (std::size_t i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
                kuo.push(s[i]);
            if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
                if (kuo.empty()) return false;
                if ((s[i] == ')' && kuo.top() == '(') || (s[i] == '}' && kuo.top() == '{') ||
                    (s[i] == ']' && kuo.top() == '['))
                    kuo.pop();
                else return false;
            }
        }
        return kuo.empty();
    }
};
```

#### Sample Solution

```c++
class Sample {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n % 2 == 1) {
            return false;
        }

        unordered_map<char, char> pairs = {
                {')', '('},
                {']', '['},
                {'}', '{'}
        };
        stack<char> stk;
        for (char ch: s) {
            if (pairs.count(ch)) {
                if (stk.empty() || stk.top() != pairs[ch]) {
                    return false;
                }
                stk.pop();
            }
            else {
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};
```

#### Note

1. Use ``` if (s.length() % 2 == 1) return false;``` to save time

2. Use key and 

   ```c++
    unordered_map<char, char> pairs = {
               {')', '('},
               {']', '['},
               {'}', '{'}
       };
   ```

to do match

3. Use ```pairs.count(ch)``` to judge whether the key exists 
