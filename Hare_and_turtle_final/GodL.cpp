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

#include <unistd.h>

int main() {
#ifdef BZ
    //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);

    //ifstream in ("prog.txt");
    unsigned long seed = mix(clock(), time(NULL), getpid());
    srand (seed);

    while (true) {
        ifstream in ("prog.txt");
        while (in.peek() != 'G' and in.peek() != 'E') {
            // wait;
        }
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