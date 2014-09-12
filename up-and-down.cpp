// David Wahler <dwahler@gmail.com>

#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;

struct state {
    state(int i, int j, bool uphill) : i(i), j(j), uphill(uphill) {};

    int i, j;
    bool uphill;

    bool operator<(const state& other) const {
        if (i != other.i) return i < other.i;
        if (j != other.j) return j < other.j;
        return !uphill && other.uphill;
    }
};

const int deltas[][2] = { { 0,-1 }, { 0,1 }, { -1,0 }, { 1,0 } };

int main() {
    int T;
    cin >> T;

    for (int testCase = 1; testCase <= T; testCase++) {
        int N, M;
        cin >> N >> M;

        vector<vector<int> > grid(N, vector<int>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> grid[i][j];
            }
        }

        deque<state> current, next;
        set<state> visited;

        current.push_back(state(0, 0, true));
        current.push_back(state(0, 0, false));

        int iteration = 0;
        bool found = false;

        while (!found) {
            while (!current.empty()) {
                const state s = current.front();
                current.pop_front();

                if ((s.i == N-1) && (s.j == M-1)) {
                    found = true;
                    break;
                }

                if (visited.find(s) != visited.end()) {
                    continue;
                }
                visited.insert(s);

                for (int delta = 0; delta < 4; delta++) {
                    const int di = deltas[delta][0], dj = deltas[delta][1];
                    const int i2 = s.i + di, j2 = s.j + dj;

                    if (i2 < 0 || i2 >= N) continue;
                    if (j2 < 0 || j2 >= M) continue;

                    const bool change_gears = (grid[i2][j2] > grid[s.i][s.j]) != s.uphill;
                    if (change_gears) {
                        next.push_back(state(i2, j2, !s.uphill));
                    } else {
                        current.push_back(state(i2, j2, s.uphill));
                    }
                }
            }

            if (found) break;

            swap(current, next);
            iteration++;
        }

        cout << iteration << endl;
    }
}
