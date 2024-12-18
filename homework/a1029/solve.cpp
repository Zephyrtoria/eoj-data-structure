#include <iostream>
#include <string>
using namespace std;

string solve(string source, string subString, string t) {
    int sourceI = 0;
    int pos = -1;
    string result = "";
    do {
        pos = source.find(subString, pos + 1);
        if (pos != string::npos) {
            while (sourceI < pos) {
                result += source[sourceI++];
            }
            sourceI += subString.size();
            result += t;
        }
    } while (pos != string::npos);
    while (sourceI < source.size()) {
        result += source[sourceI++];
    }
    return result;
}

int main() {
    string source;
    string subString;
    string t;
    getline(cin, source);
    getline(cin, subString);
    getline(cin, t);

    cout << solve(source, subString, t) << endl;
    return 0;
}