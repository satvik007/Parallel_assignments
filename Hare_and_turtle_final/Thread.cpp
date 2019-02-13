// compile with flags "-std=c++14 -pthread"

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using ll = int64_t;
using ld = long double;
using ull = uint64_t;
using namespace std;
using namespace __gnu_pbds;
typedef vector <int> vi;
typedef pair <int, int> ii;

const int INF = 1 << 30;

#define maxn 100010

//#include <thread>
#include <pthread.h>
#include <unistd.h>

int tur = 0, har = 0;
int finish = 20;

int new_tur = 0, new_har = 0;
int hare_sleep = 0;
int mod = 5;
bool f = false;

void* hare_object (void* a) {
    if (hare_sleep) {
        hare_sleep--;
        new_har = har;
    } else if (tur > har) {
        new_har = har + 3;
    } else {
        hare_sleep = rand() % mod;
    }
    return NULL;
}

void* turtle_object (void* a) {
    new_tur = tur + 1;
    return NULL;
}

void* reporter_object (void* a) {
    cout << "Hare - " << setw (6) << har << " " << "    Turtle - " << setw (6) << tur << "\n";
    return NULL;
}

void* god_object (void* a) {
    if (f) {
        ofstream out("prog.txt");
        out << "God wants input\n";
    }
    if (!f)
        cout << "Enter 1 to reposition hare: ";
    int u; cin >> u;

    if (u == 1) {
        if (!f)
            cout << "Enter the hare location: ";
        cin >> har;
    }

    if (!f)
        cout << "Enter 1 to reposition turtle: ";
    cin >> u;

    if (u == 1) {
        if (!f)
            cout << "Enter the turtle location: ";
        cin >> tur;
    }
    
    return NULL;
}

int main(int argc, char **argv) {
#ifndef BZ
    //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);
#endif

    for (int i = 1; i < argc; i++) {
        string c (argv[i]);
        if (c == "-h") {
            cout << "Available Parameters: \n\n";
            cout << "-h for this help menu\n";
            cout << "-t for automated testing\n\n";
        } else if (c == "-t") {
            int pid = fork();
            if (pid == -1) {
                cout << "fork can't be done.\n";
                exit(0);
            } else if (pid == 0) {
                int ind = 0;
                for (int j = strlen(argv[0]); j >= 0; j--) {
                    if (argv[0][j] == '/') {
                        ind = j;
                        break;
                    }
                }
                string p = string(argv[0]).substr (0, ind);
                string q = p + "/GodL";
                char *args[] = {"./GodL", NULL};
                int ret = execvp("./GodL", args);
                cout << "Return value: " << ret << "\n";

                if (ret < 0) {
                    cout << "Exec failed\n";
                    exit(0);
                }
            }
            f = true;
            freopen ("god.txt", "r", stdin);
        }
    }
    srand (time(0));

    pthread_t hare, turtle, reporter;
    int iret1, iret2, iret3;

    while (tur < finish and har < finish) {
        iret1 = pthread_create( &hare, NULL, hare_object, (void*) NULL);
        iret2 = pthread_create( &turtle, NULL, turtle_object, (void*) NULL);
        iret3 = pthread_create( &reporter, NULL, reporter_object, (void*) NULL);

        pthread_join( hare, NULL);
        pthread_join( turtle, NULL);
        pthread_join( reporter, NULL);

        har = new_har;
        tur = new_tur;

        god_object(NULL);
    }

    iret3 = pthread_create( &reporter, NULL, reporter_object, (void*) NULL);
    pthread_join( reporter, NULL);

    har = min (har, finish);
    tur = min (tur, finish);

    if (f) {
        ofstream out ("prog.txt");
        out << "End of Program\n";
    }

    if (har == tur) {
        cout << "Tie\n";
    } else if (har > tur) {
        cout << "Hare wins\n";
    } else {
        cout << "Turtle wins\n";
    }

}