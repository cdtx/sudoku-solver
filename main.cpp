#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    for (int i = 0; i < 9; i++) {
        string line;
        getline(cin, line);
        cout << line << endl;
    }
}
