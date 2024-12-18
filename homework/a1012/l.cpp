#include <iostream>
#include <string>
using namespace std;

#define NUMBER 1000000000

int guessWhat()
{
    int left = -int(NUMBER);
    int right = int(NUMBER);

    string input;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        cout << mid << endl;
        cin >> input;

        if (input == "big")
            right = mid - 1;
        else if (input == "small")
            left = mid + 1;
        else
            return mid;
        input = "";
    }
    return left;
}

int main()
{
    guessWhat();
    return 0;
}
