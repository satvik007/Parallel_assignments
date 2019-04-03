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

pthread_mutex_t lhar;
pthread_mutex_t ltur;
pthread_mutex_t lrep1;
pthread_mutex_t lrep2;
pthread_mutex_t lgod;

void* hare_object (void* a) {
    while (har < finish and tur < finish) {
        pthread_mutex_lock(&lhar);
        if (hare_sleep) {
            hare_sleep--;
            new_har = har;
        } else if (tur > har) {
            new_har = har + 3;
        } else {
            hare_sleep = rand() % mod;
        }
        pthread_mutex_unlock(&lrep1);
    }
    return NULL;
}

void* turtle_object (void* a) {
    while (har < finish and tur < finish) {
        pthread_mutex_lock(&ltur);
        new_tur = tur + 1;
        pthread_mutex_unlock(&lrep2);
    }
    return NULL;
}

void* reporter_object (void* a) {
    while (har < finish and tur < finish) {
        pthread_mutex_lock(&lrep1);
        pthread_mutex_lock(&lrep2);
        har = new_har;
        tur = new_tur;

        cout << "Hare - " << setw (6) << har << " " << "    Turtle - " << setw (6) << tur << "\n";
        pthread_mutex_unlock(&lgod);
    }

    return NULL;
}

void* god_object (void* a) {
    while (har < finish and tur < finish) {
        pthread_mutex_lock(&lgod);
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

        pthread_mutex_unlock(&lhar);
        pthread_mutex_unlock(&ltur);

    }

    return NULL;
}

unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

int main(int argc, char **argv) {
#ifndef BZ
    //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    //ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);
#endif

    pthread_mutex_init(&lhar, NULL);
    pthread_mutex_init(&ltur, NULL);
    pthread_mutex_init(&lrep1, NULL);
    pthread_mutex_init(&lrep2, NULL);
    pthread_mutex_init(&lgod, NULL);

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
                string q = p + "/GodL.out";
                char *args[] = {"./GodL.out", (char*) NULL};
                int ret = execvp("./GodL.out", args);
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
    unsigned long seed = mix(clock(), time(NULL), getpid());

    srand (seed);

    pthread_t hare, turtle, reporter, god;
    int iret1, iret2, iret3, iret4;

    pthread_mutex_lock(&lgod);
    pthread_mutex_lock(&lrep1);
    pthread_mutex_lock(&lrep2);


    iret1 = pthread_create( &hare, NULL, hare_object, (void*) NULL);
    iret2 = pthread_create( &turtle, NULL, turtle_object, (void*) NULL);
    iret4 = pthread_create( &god, NULL, god_object, (void*) NULL);
    iret3 = pthread_create( &reporter, NULL, reporter_object, (void*) NULL);


    pthread_join( hare, NULL);
    pthread_join( turtle, NULL);
    pthread_join( reporter, NULL);
    pthread_join( god, NULL);

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