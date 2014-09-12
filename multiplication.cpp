#include <iostream>

using namespace std;

int main()
{
    int K;
    cin >> K;
    for (int testCase = 1; testCase <= K; testCase++) {
        int n, m;
        cin >> n >> m;

        cout << ((m * (m + 1)) / 2) * ((n * (n + 1)) / 2) << endl;
    }

}
