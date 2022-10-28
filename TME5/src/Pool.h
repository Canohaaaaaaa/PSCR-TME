#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) : queue(qsize) {}
	void submit (Job * job){
		queue.push(job);
	}
	~Pool() {
		return;
	}
	void poolWorker(Queue<Job> & queue){
		while(true){
			Job *j = queue.pop();
			if(j == nullptr){
				break;
			}
			j->run();
			delete j;
		}
	}

	void stop(){
		queue.setBlocking(false);
		for(auto & t: threads){
			t.join();
		}
	}
	void start(int nbThread){
		for(int i=0; i < nbThread; i++){
			threads.emplace_back(std::thread(&Pool::poolWorker, this, std::ref(queue)));
		}
	}
};
}
