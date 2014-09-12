// David Wahler <dwahler@gmail.com>
//
// Uses the alternating-path algorithm, which is a specialization of max-flow
// for solving matching problems.

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#define D(x) 

using namespace std;

int main() {
    int T;
    cin >> T;

    for (int testCase = 1; testCase <= T; testCase++) {
        int N;
        cin >> N;
        string line;
        getline(cin, line);

        map<string, int> student_names;
        vector<vector<int> > class_students(N);
        vector<vector<int> > student_classes;
        vector<bool> active_student;
        vector<int> capacity_remaining(N);
        int total = 0;

        for (int i = 0; i < N; i++) {
            getline(cin, line);
            istringstream iss(line);

            iss >> capacity_remaining[i];
            string name;
            while (iss >> name) {
                map<string, int>::const_iterator it = student_names.find(name);
                int id;

                if (it != student_names.end()) {
                    id = it->second;
                } else {
                    id = student_names.size();
                    student_names[name] = id;
                    student_classes.push_back(vector<int>());
                    active_student.push_back(false);
                }

                class_students[i].push_back(id);
                student_classes[id].push_back(i);
            }
        }

        const int M = student_names.size();
        vector<vector<bool> > active(N, vector<bool>(M));

        while (true) {
            // BFS to find augmenting path
            vector<int> class_parent(N, -1), student_parent(M, -1);

            vector<int> current_students;
            for (int i = 0; i < M; i++) {
                if (!active_student[i]) current_students.push_back(i);
            }

            int end_class = -1;

            while (!current_students.empty()) {
                D(cerr << "iteration" << endl);
                vector<int> current_classes;

                for (int student : current_students) {
                    for (int class_ : student_classes[student]) {
                        if (active[class_][student]) continue;
                        if (class_parent[class_] != -1) continue;
                        D(cerr << "student " << student << " -> class " << class_ << endl);

                        class_parent[class_] = student;
                        current_classes.push_back(class_);
                    }
                }

                vector<int> next_students;

                for (int class_ : current_classes) {
                    if (capacity_remaining[class_] > 0) {
                        D(cerr << "capacity of " << class_ << " is " << capacity_remaining[class_] << endl);
                        end_class = class_;
                        break;
                    }
                    for (int student : class_students[class_]) {
                        if (!active[class_][student]) continue;
                        if (student_parent[student] != -1) continue;
                        D(cerr << "class " << class_ << " -> student " << student << endl);

                        student_parent[student] = class_;
                        next_students.push_back(student);
                    }
                }
                if (end_class != -1) break;

                swap(current_students, next_students);
            }

            if (end_class == -1) break;

            int class_ = end_class;
            while (true) {
                int student = class_parent[class_];
                active[class_][student] = true;
                D(cerr << "activating student " << student << " -> class " << class_ << endl);

                if (!active_student[student]) {
                    D(cerr << "activating student " << student << endl);
                    active_student[student] = true;
                    break;
                }

                class_ = student_parent[student];
                active[class_][student] = false;
                D(cerr << "deactivating student " << student << " -> class " << class_ << endl);
            }

            capacity_remaining[end_class]--;
            total++;
        }


        cout << total << endl;
    }
}
