#include "barrier.h"


barrier::barrier(int num) : count_(num), col_of_threads(num), state_forward(true) { }

auto barrier::wait_for_others() -> void const 
{
	unique_lock<mutex> lock(mtx);

	if (!state_forward) 
	{

		count_++;
		if (count_ == col_of_threads)
		{
			state_forward = true;
			cv.notify_all();
		}
		else
		{
			cv.wait(lock, [&]() { return state_forward == true; });
		}
	}
	else 
	{
		count_--;
		if (count_==0)
		{
			state_forward = false;
			cv.notify_all();
		}
		else
		{
			cv.wait(lock, [&](){ return state_forward == false; });
		}
	}
}