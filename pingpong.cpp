#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

thread::id ID;

size_t N;
bool check_id = true;
size_t I = 0;
string CUR = "PONG";

void PingPong() {
    if (check_id) {
        ID = this_thread::get_id();
        check_id = false;
    }

    if (this_thread::get_id() == ID) {
        while (I < N) {
            if (CUR == "PING") {
                cout << this_thread::get_id() << ": PONG" << endl;
                I++;
                CUR = "PONG";
            }
            else if (CUR == "PONG") {
                this_thread::sleep_for(10ms);
            }
            else {
                cout << "ERROR: wrong input data" << endl;
                return;
            }
        }
    } else {
        while (I < N) {
            if (CUR == "PONG") {
                cout << this_thread::get_id() << ": PING" << endl;
                I++;
                CUR = "PING";
            }
            else if (CUR == "PING") {
                this_thread::sleep_for(10ms);
            }
            else {
                cout << "ERROR: wrong input data" << endl;
                return;
            }
        }
    }
    return;
}

int main() {
    cin >> N;
    thread th(PingPong);
    this_thread::sleep_for(10ms);
    PingPong();
    
    th.join();
    return 0;
}