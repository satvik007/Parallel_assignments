#include <iostream>
#include <string>
#include <regex>

using namespace std;

int flag, n, thread_count;
long long sum;

void* thread_sum (void* rank) {
    long my_rank = (long) rank;
    double factor, my_sum = 0.0;
    long long i;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    
    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = - 1.0;
    
    for (i = my_first_i; i < my_last_i; i++, factor = - factor)
        my_sum += factor/(2*i+1);

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

int calculate_n (string arg_val) {
    regex intended("[0-9]+");
    if (regex_match(arg_val, intended) and arg_val.size() <= 9) {
        int arg_val_int = stoi (arg_val);
        if (arg_val_int > 0 and arg_val_int <= 1e9) {
            return arg_val_int;
        }
    } 
    throw -1;
}

void init () {
    flag = 0;
    sum = 0;
}

int main (int argc, char **argv) {

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
        } else {
            cerr << "Argument type not recognized.\n";
            return 1;
        }
    }

    init();



    return 0;
}
