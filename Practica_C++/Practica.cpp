#include <iostream>
#include <cstring>
#include <algorithm>

//https://roadmap.sh/cpp

using namespace std;

int main() {

    int a;

    cout << "Enter a number: " << endl;

    cin >> a;

    for (int i = a; i >= 1; i--) {
        cout << i << " ";
    }
    return 0;
}