#include <bits/stdc++.h>
using namespace std;

string file_name (string arg_val) {
    regex intended("([0-9a-zA-Z_]+).txt");
    if (regex_match(arg_val, intended) and arg_val.size() <= 30) {
        return arg_val;
    } 
    throw -1;
}

int main (int argc, char **argv) {

    string name = "busy_wait.txt";
    string out_name = "busy_wait_final.txt";

    if (!(argc % 2)) {
        cerr << "Arguments error\n";
        return 1;
    }

    for (int i = 1; i < argc; i += 2) {
        string type (argv[i]);
        string arg_val (argv[i + 1]);
        if (type == "-f") {
            try {
                name = file_name (arg_val);
            } catch (...) {
                cerr << "Invalid file name\n";
                return 1;
            }
        } else if (type == "-o") {
            try {
                out_name = file_name (arg_val);
            } catch (...) {
                cerr << "Invalid file name\n";
                return 1;
            }
        } else {
            cerr << "Argument type not recognized.\n";
            return 1;
        }
    }

    if (freopen (name.c_str(), "r", stdin)) {

    } else {
        cerr << "Cannot open file\n";
        return -1;
    }

    freopen (out_name.c_str(), "w", stdout);

    cout << fixed << setprecision (5);
    string s;
    vector <double> a;
    vector <int> b;

    while (getline(cin, s)) {
        stringstream sin(s);
        string u;
        string last;
        while (sin >> u) {
            if (last == "Threads:") {
                b.push_back (stoi(u));
            }
            last = u;
        }
        a.push_back (stod(u));
    }

    for (int i = 0; i < a.size(); i += 5) {
        double avg = 0;
        double max_value = 0;
        double min_value = 1e9;
        for (int j = 0; j < 5; j++) {
            avg += a[i + j];
            max_value = max (max_value, a[i + j]);
            min_value = min (min_value, a[i + j]);
        }
        avg /= 5;
        cout << "Threads: " << b[i] << "\tAverage: " << avg << "\tMax: " << max_value << "\tMin: " << min_value << "\n";
    }

    return 0;
}