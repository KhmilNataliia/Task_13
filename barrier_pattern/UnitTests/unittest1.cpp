#include "stdafx.h"
#include "CppUnitTest.h"
#include <thread>
#include <chrono>

#include "catch.hpp"
#include "barrier.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace this_thread;
using namespace chrono;

namespace UnitTests
{		
	vector<int> res;
	void f(int a, barrier *br)
	{
		res.push_back(a);
		sleep_for(seconds(4));
		br->wait_for_others();

	}
	void f2(int b, barrier *br)
	{
		res.push_back(b);
		sleep_for(seconds(2));
		br->wait_for_others();
		res.push_back(-1);
	}

	TEST_CASE("barrier")
	{
		res.clear();
		barrier *br =new barrier(2);
		thread t1 = thread(f2, 1, br);
		thread t2 = thread(f, 2, br);
		thread t3 = thread(f, 3, br);
		thread t4 = thread(f, 4, br);
		
		t1.join();
		t2.join();
		t3.join();
		t4.join();

		REQUIRE(res[res.size()-1]==-1);
	};

	TEST_CASE("barrier2.0")
	{
		res.clear();
		barrier *br = new barrier(2);
		thread t1 = thread(f2, 1, br);
		thread t2 = thread(f, 2, br);
		thread t3 = thread(f, 3, br);
		thread t4 = thread(f, 4, br);
		thread t5 = thread(f, 5, br);
		thread t6 = thread(f, 6, br);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();

		REQUIRE(res[res.size() - 1] == -1);
	};

	TEST_CASE("barrier3.0")
	{
		res.clear();
		barrier *br = new barrier(3);
		thread t1 = thread(f, 1, br);
		thread t2 = thread(f, 2, br);
		thread t3 = thread(f2, 3, br);
		thread t4 = thread(f, 4, br);
		thread t5 = thread(f, 5, br);
		thread t6 = thread(f, 6, br);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();

		REQUIRE(res[res.size() - 1] == -1);
	};
}