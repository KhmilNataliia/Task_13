#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "barrier.h"

using namespace std;
using namespace this_thread;
using namespace chrono;


barrier br = barrier(2);

void func(string n)
{
	string res = "thread num: ";
	res += n+" ";
	cout << res << endl;
	sleep_for(seconds(2));
	br.wait_for_others();
	cout << " after waiting " << endl;
}


int main()
{
	thread t1 = thread(func, "1");
	thread t2 = thread(func, "2");
	thread t3 = thread(func, "3");
	thread t4 = thread(func, "4");

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	system("pause");
	return 0;
}