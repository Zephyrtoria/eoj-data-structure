#include <iostream>
#include <list>
#include <string>
using namespace std;

string toString(list<char>& l) {
    auto i = l.begin();
    string result = "";
    while (i != l.end()) {
        result += *i;
        i++;
    }
    return result;
}

void solve(list<char>& str, int x, int y, string& a, string& b) {
    string cutDown = "";
    auto curIdx = str.begin();
    int count = 1;
    while (count < x) {
        count++;
        curIdx++;
    }
    while (count <= y) {
        cutDown += *curIdx;
        str.erase(curIdx++);
        count++;
    }

    string s = toString(str);
    string merge = a + b;
    int idx = s.find(merge);
    if (idx != string::npos) {
        int startIdx = idx + a.length();

        auto curIdx = str.begin();
        count = 1;
        while (count <= startIdx) {
            curIdx++;
            count++;
        }
        for (int i = 0, size = cutDown.length(); i < size; i++) {
            str.insert(curIdx, cutDown[i]);
        }

    } else {
        for (int i = 0, size = cutDown.length(); i < size; i++) {
            str.push_back(cutDown[i]);
        }
    }
}

int main(void) {
    string s;
    cin >> s;
    list<char> str;
    for (int i = 0; i < s.size(); i++) {
        str.push_back(s[i]);
    }

    int T;
    cin >> T;
    while (T--) {
        int x, y;
        string a, b;
        cin >> x >> y >> a >> b;
        solve(str, x, y, a, b);
    }
    cout << toString(str) << endl;

    return 0;
}