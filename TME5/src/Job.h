#pragma once
#include <thread>
#include <chrono>
namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple

}
