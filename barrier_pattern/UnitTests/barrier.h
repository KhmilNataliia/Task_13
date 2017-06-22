#include <condition_variable>
#include <mutex>

using namespace std;

class barrier
{
	mutex mtx;
	condition_variable cv;
	int count_ = 0;
	int col_of_threads = 0;
	bool state_forward;
public:
	barrier(int num);
	virtual auto wait_for_others() -> void const final;
};