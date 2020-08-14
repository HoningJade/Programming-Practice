/*
题目：将带评论的json字符串去掉评论返回。
基本思路：找到“//”的话，跳过直至行尾;
 找到“/”的话，找下一个"/",并将这里中间的跳过。
 注意：对于getline读入的字符串，是不带有回车符的，需要读的时候手动加一下。*/

#include <bits/stdc++.h>

using namespace std;

string simplify(string s) {
    string ans;
    int i = 0;
    while (i < s.size()) {
        if (s[i] == '/') {
            if (i + 1 < s.size() && s[i + 1] == '/') {
                i += 2;  // 双斜杠
                while (i < s.size() && s[i] != '\n') i++; //跳到下一行
                ans += s[i++];  //读入下一行第一个
            } else if (i + 1 < s.size() && s[i + 1] == '*') {
                i += 2;  // 多行注释
                while (i + 1 < s.size() && (s[i] != '*' || s[i + 1] != '/')) i++;
                i += 2;
            } else
                ans += s[i++];
        } else
            ans += s[i++];
    }
    return ans;
}


int main() {
    string s, line;
    // 要读文件才可结束，此处主要展示work()
    while (getline(cin, line)) {
        if(cin) break;
        s += line + '\n'; // 把cin变成一个string
    }
    cout << simplify(s);
    return 0;
}
