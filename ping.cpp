// David Wahler <dwahler@gmail.com>
// adapted from Ping_artur.java, from the SER 2013 ACM-ICPC regional contest

#include <iostream>
#include <string>

using namespace std;

int main() {
    int T;
    cin >> T;

    for (int testCase = 1; testCase <= T; testCase++) {
        string s;
        cin >> s;

        bool first = true;
        for (int i = 1; i < s.length(); i++) {
            if (s[i] == '1') {
                if (!first) cout << " ";
                first = false;
                cout << i;
                for (int j = i; j < s.length(); j+=i) {
                    s[j] = '1' - s[j] + '0';
                }
            }
        }
        cout << endl;
    }
}

