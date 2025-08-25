#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;
int main() {

    int a;
    char word[] = "Diego";

    reverse(word, word + strlen(word));

    cout << word;

    cout << " ";
    cin >> a;
    return 0;
}