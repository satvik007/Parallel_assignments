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


int finish = 20;

int main() {
#ifdef BZ
    //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);

    //ifstream in ("prog.txt");

    while (true) {
        ifstream in ("prog.txt");
        while (in.peek() != 'G' and in.peek() != 'E') {
            // wait;
        }
        cout << "GodL writes\n";
        flush (cout);
        if (in.peek() == 'E') break;
        ofstream out ("god.txt");
        int u = rand() % 2;
        out << u << "\n";
        if (u != 0) {
            int v = rand() % (finish + 1);
            out << v << "\n";
        }
        u = rand() % 2;
        out << u << "\n";
        if (u != 0) {
            int v = rand() % (finish + 1);
            out << v << "\n";
        }
        //cout << "GodL writes again.\n";
    }

}