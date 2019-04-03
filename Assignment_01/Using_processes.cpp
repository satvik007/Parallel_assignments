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

#include <unistd.h>

int main() {
#ifdef BZ
    freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);
#endif

    int god2har[2];
    int god2tur[2];
    int har2rep[2];
    int tur2rep[2];
    int rep2god[2];

    pipe (god2har);
    pipe (god2tur);
    pipe (har2rep);
    pipe (tur2rep);
    pipe (rep2god);

    char buf[16];

    int har = 0, tur = 0;
    int finish = 20;
    int mod = 5;

    vi pid;

    int n1 = fork();
    // hare
    if (n1 == 0) {
        int sleep = 0;
        while (true) {
            read(god2har[0], buf, 16);
            tur = atoi (buf);

            if (sleep) {
                sleep--;
            } else if (har < tur) {
                har += 3;
            } else {
                sleep = rand () % mod;
            }
            strcpy (buf, to_string (har).c_str());
            write (har2rep[1], buf, 16);
            if (har >= finish or tur >= finish)
                break;
        }
        strcpy (buf, to_string (har).c_str());
        write (har2rep[1], buf, 16);
        return 0;
    }

    pid.push_back (n1);

    int n2 = fork ();
    // turtle
    if (n2 == 0) {
        while (true) {
            read(god2tur[0], buf, 16);
            har = atoi (buf);
            tur++;
            strcpy (buf, to_string (tur).c_str());
            write (tur2rep[1], buf, 16);
            if (tur >= finish or har >= finish)
                break;
        }
        strcpy (buf, to_string (tur).c_str());
        write (tur2rep[1], buf, 16);
        return 0;
    }

    pid.push_back (n2);

    int n3 = fork();
    // reporter
    if (n3 == 0) {
        int cnt = 0;
        while (true) {
            if (cnt > 10000) {
                break;
            }
            read(har2rep[0], buf, 16);
            har = atoi (buf);
            read(tur2rep[0], buf, 16);
            tur = atoi (buf);
            cout << "Hare - " << setw (6) << har << "   Turtle - " << setw (6) << tur << "\n";

            strcpy (buf, to_string (har).c_str());
            write (rep2god[1], buf, 16);
            strcpy (buf, to_string (tur).c_str());
            write (rep2god[1], buf, 16);

            if (tur >= finish or har >= finish) break;
            cnt++;
        }
        strcpy (buf, to_string (har).c_str());
        write (rep2god[1], buf, 16);
        strcpy (buf, to_string (tur).c_str());
        write (rep2god[1], buf, 16);
        return 0;
    }

    pid.push_back (n3);

    // driver
    while (true) {
        cout << "Enter 1 to reposition hare: ";
        int u; cin >> u;

        if (u == 1) {
            cout << "Enter the hare location: ";
            cin >> har;
        }

        cout << "Enter 1 to reposition turtle: ";
        cin >> u;

        if (u == 1) {
            cout << "Enter the turtle location: ";
            cin >> tur;
        }

        if (har >= finish or tur >= finish)
            break;

        strcpy (buf, to_string (tur).c_str());
        write (god2har[1], buf, 16);
        strcpy (buf, to_string (har).c_str());
        write (god2tur[1], buf, 16);

        read(rep2god[0], buf, 16);
        har = atoi (buf);
        read(rep2god[0], buf, 16);
        tur = atoi (buf);

        if (har >= finish or tur >= finish)
            break;

    }

    strcpy (buf, to_string (tur).c_str());
    write (god2har[1], buf, 16);
    strcpy (buf, to_string (har).c_str());
    write (god2tur[1], buf, 16);

    if (har == tur) {
        cout << "Tie\n";
    } else if (har > tur) {
        cout << "Hare wins\n";
    } else {
        cout << "Turtle wins\n";
    }

}