#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int N = 5000010;

int *getNext(char *needle) {
    int size = strlen(needle);
    int *next = new int[size];
    next[0] = 0;
    int j = 0;
    for (int i = 1; i < size; i++) {
        while (j > 0 && needle[i] != needle[j]) {
            j = next[j - 1];
        }
        if (needle[i] == needle[j]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}

int strStr(char *haystack, char *needle) {
    int *next = getNext(needle);
    int sizeH = strlen(haystack);
    int sizeN = strlen(needle);

    if (sizeH == 0 || sizeN == 0 || sizeH < sizeN) {
        return -1;
    }

    int i = 0, j = 0;
    while (i < sizeH) {
        if (j > 0 && haystack[i] != needle[j]) {
            j = next[j - 1];
            continue;
        } else if (haystack[i] == needle[j]) {
            j++;
        }

        if (j == sizeN) {
            delete next;
            return i - j + 1;
        }
        i++;
    }
    delete next;
    return -1;
}

int main(void) {
    char *haystack = new char[N];
    char *needle = new char[N];
    cin >> haystack >> needle;
    cout << strStr(haystack, needle) << endl;
    delete haystack;
    delete needle;
    return 0;
}