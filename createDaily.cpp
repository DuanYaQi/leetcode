#include<iostream>

using namespace std;

int main() {
    int year = 2022;
    int maxD = 31;
    int month = 3;

    for (int i = 1; i <= maxD; ++i) {
        //cout << year << "-" << "" << endl;
        printf("%d-%02d-%02d\n", year, month, i);
    }


    return 0;
}