#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int n;
string s[N];

int getMaxLength(string& str) {
    int size = str.size();
    int* next = new int[size];

    next[0] = 0;
    int j = 0;
    for (int i = 1; i < size; i++) {
        while (j > 0 && str[i] != str[j]) {
            j = next[j - 1];
        }
        if (str[i] == str[j]) {
            j++;
        }
        next[i] = j;
    }
    return next[size - 1];
}

string solve() {
    string result = s[0];
    for (int i = 1; i < n; i++) {
        // aaa#aaa 主动添加井号来分隔两个字符串
        // result只需要比较添加的字符串长度范围
        string temp;
        if (result.size() < s[i].size()) {
            temp = s[i] + "#" + result;
        } else {
            temp = s[i] + "#" + result.substr(result.size() - s[i].size());
        }
        int next = getMaxLength(temp);
        result += s[i].substr(next);
    }
    return result;
}

int main(void) {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    cout << solve() << endl;
    return 0;
}