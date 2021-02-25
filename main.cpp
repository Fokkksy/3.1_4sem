#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <chrono>
#include <algorithm>
#include <random>

const int N = 100000;

using namespace std;

class Timer {
public:
	Timer() :
		moment_begin(chrono::steady_clock::now()), moment_rest(0) {}
	void pause() {
		auto end = chrono::steady_clock::now();
		moment_rest = chrono::duration_cast <chrono::microseconds> (end - moment_begin);
	}

	void restart() {
		moment_begin = chrono::steady_clock::now();
	}
	~Timer() {
		auto end = chrono::steady_clock::now();
		no_pause_before_end = true;
		if (no_pause_before_end) {
			moment_rest = moment_rest + chrono::duration_cast <chrono::microseconds> (end - moment_begin);

		}
		cout << "      " << moment_rest.count() << "      ";
	}


private:
	chrono::steady_clock::time_point moment_begin;
	chrono::microseconds moment_rest;
	bool no_pause_before_end = false;
};


int main(){

	std::default_random_engine dre;
	std::uniform_real_distribution<double> myrandom(0, 100);

    std::set<int> set_element;
    std::vector<int> v_generated(0);
    std::vector<int> v_element(0);
	std::array<int, N> arr;

    for (int count = 0; count < N; ++count) {
        v_generated.push_back(myrandom(dre));
    }
	cout << "SET_TIME: ";
	{Timer time;
	for (int count = 0; count < N; ++count) {
		set_element.insert(v_generated[count]);
		}
	}
	cout << "\nVECTOR_TIME: ";
	{Timer time;
	for (int count = 0; count < N; ++count) {
		v_element.push_back(v_generated[count]);
	}
	std::sort(begin(v_element), end(v_element), std::greater<int>());}
	cout << "\nARRAY_TIME: ";
	{Timer time;
	for (int count = 0; count < N; ++count) {
		arr[count]=v_generated[count];
	}
	std::sort(begin(arr), end(arr), std::greater<int>()); }
    
}