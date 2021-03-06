#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <mutex>

using namespace std;

int flag, thread_count;
long long n, sum;
string file;

mutex mtx;

void* thread_sum (void* rank) {
    long my_rank = (long) rank;
    long long my_sum = 0;
    long long i;
    long long my_n;
    long long my_first_i;
    long long my_last_i;

    my_n = (n + thread_count - 1) / thread_count;
    my_first_i = my_n * my_rank;
    my_last_i = min (my_first_i + my_n, n);

    // mtx.lock();
    // cout << my_rank << " " << my_first_i << " " << my_last_i << "\n";
    // mtx.unlock();

    if (my_first_i > n) {
        return NULL;
    }
    
    for (i = my_first_i; i < my_last_i; i++)
        my_sum += i;

    while (flag != my_rank);
    
    sum += my_sum;
    flag = (flag+1) % thread_count;
    
    return NULL;
}

int calculate_thread_count (string arg_val) {
    regex intended("[0-9]+");
    if (regex_match(arg_val, intended) and arg_val.size() <= 9) {
        int arg_val_int = stoi (arg_val);
        if (arg_val_int > 0 and arg_val_int <= 1000) {
            return arg_val_int;
        }
    } 
    throw -1;
}

long long calculate_n (string arg_val) {
    regex intended("[0-9]+");
    if (regex_match(arg_val, intended) and arg_val.size() <= 18) {
        long long arg_val_int = stoll (arg_val);
        if (arg_val_int > 0 and arg_val_int <= 1e18) {
            return arg_val_int;
        }
    } 
    throw -1;
}

string file_name (string arg_val) {
    regex intended("([0-9a-zA-Z_]+).txt");
    if (regex_match(arg_val, intended) and arg_val.size() <= 30) {
        return arg_val;
    } 
    throw -1;
}

void init () {
    thread_count = 4;
    n = 10;
    flag = 0;
    sum = 0;
}

int main (int argc, char **argv) {

    clock_t begin = clock();
    init();

    if (!(argc % 2)) {
        cerr << "Arguments error\n";
        return 1;
    }

    for (int i = 1; i < argc; i += 2) {
        string type (argv[i]);
        string arg_val (argv[i + 1]);
        if (type == "-t") {
            try {
                thread_count = calculate_thread_count(arg_val);
            } catch (...) {
                cerr << "Invalid thread count\n";
                return 1;
            }
        } else if (type == "-n") {
            try {
                n = calculate_n(arg_val);
            } catch (...) {
                cerr << "Invalid n\n";
                return 1;
            }
        } else if (type == "-f") {
            try {
                file = file_name (arg_val);
            } catch (...) {
                cerr << "Invalid file name\n";
                return 1;
            }
        } else {
            cerr << "Argument type not recognized.\n";
            return 1;
        }
    }

    vector <thread> threads (thread_count);
    int iret[thread_count];

    for (int i = 0; i < thread_count; i++) {
        threads[i] = thread(thread_sum, (void*) (long) i);
        //iret[i] = pthread_create( &threads[i], NULL, thread_sum, (void*) (long) i);
    }

    for (int i = 0; i < thread_count; i++) {
        threads[i].join();
    }

    //cout << sum << "\n";

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    if (!file.empty()) {
        freopen(file.c_str(), "a+", stdout);
    }

    cout << "n: " << n << "    Threads: " << thread_count;
    cout << "   Time used : " << elapsed_secs << "\n";

    return 0;
}
