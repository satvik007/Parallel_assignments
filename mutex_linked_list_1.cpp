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

#include <pthread.h>
#include <unistd.h>

struct Node {
    int val;
    Node* next;
};

Node* create_new_node (int val) {
    Node* new_node = new Node;
    new_node -> val = val;
    return new_node;
}

int main(int argc, char *argv[]) {
#ifdef BZ
    freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
#endif

    cout << argc << "\n";
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << "\n";
    }
    
//    int n = 1000;
//    if (argc == 1) {
//        n = stoi (argv[0]);
//    }
//
//    //ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);
//
//    pthread_mutex_t * common = nullptr;
//    pthread_mutex_init (common, nullptr);
//
//    Node *root = create_new_node (0);
//    
//
//
//
//    pthread_mutex_destroy (common);


}