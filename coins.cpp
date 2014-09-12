// David Wahler <dwahler@gmail.com>

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int C;
    cin >> C;

    for (int testCase = 1; testCase <= C; testCase++) {
        int n;
        cin >> n;

        vector<int> coins(n);
        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }

        int best[n][n];
        for (int i = 0; i < n; i++) {
            best[i][i] = 0;
        }

        for (int remaining = 2; remaining <= n; remaining++) {
            for (int start = 0; start <= n - remaining; start++) {
                int end = start + remaining - 1;

                if (remaining % 2 == 0) {
                    // my turn
                    best[start][end] = max(
                            coins[start] + best[start+1][end],
                            best[start][end-1] + coins[end]);
                } else {
                    // opponent's turn
                    best[start][end] = min(
                            best[start+1][end],
                            best[start][end-1]);
                }
            }
        }

        cout << best[0][n-1] << endl;
    }
}
