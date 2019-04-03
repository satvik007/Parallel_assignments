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

#include <thread>

int main() {
#ifdef BZ
    freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);
#endif

    int tur = 0, har = 0;
    int finish = 20;

    int new_tur = 0, new_har = 0;
    int hare_sleep = 0;
    int mod = 5;

    function <void ()> hare_object = [&] () {
        if (hare_sleep) {
            hare_sleep--;
            new_har = har;
        } else if (tur > har) {
            new_har = har + 3;
        } else {
            hare_sleep = rand() % mod;
        }
    };

    function <void ()> turtle_object = [&] () {
        new_tur = tur + 1;
    };

    function <void ()> reporter_object = [&] () {
        cout << "Hare - " << setw (6) << har << " " << "    Turtle - " << setw (6) << tur << "\n";
    };

    while (tur < finish and har < finish) {
        thread hare (hare_object);
        thread turtle (turtle_object);
        thread reporter (reporter_object);

        hare.join();
        turtle.join();
        reporter.join();

        har = new_har;
        tur = new_tur;

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
    }
    thread reporter (reporter_object);
    reporter.join();


    if (har == tur) {
        cout << "Tie\n";
    } else if (har > tur) {
        cout << "Hare wins\n";
    } else {
        cout << "Turtle wins\n";
    }

}