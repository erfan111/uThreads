/*
 * Cluster.h
 *
 *  Created on: Oct 23, 2014
 *      Author: Saman Barghi
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_
#include "ReadyQueue.h"
#include "global.h"
#include <vector>
#include <mutex>

class Cluster {
	friend class kThread;
private:
	ReadyQueue readyQueue;								//There is one ready queue per cluster

public:
	Cluster();
	virtual ~Cluster();

	Cluster(const Cluster&) = delete;
	const Cluster& operator=(const Cluster&) = delete;

	static Cluster	defaultCluster;						//Default cluster
	static Cluster	syscallCluster;						//Syscall cluster
	static std::vector<Cluster*> clusters;				//List of all clusters
	static std::mutex mtx;

	int clusterID; 										//Id of this cluster



	static void invoke(funcvoid1_t, void*) __noreturn;	//Function to invoke the run function of a uThread
	void uThreadSchedule(uThread*);						//Put ut in the ready queue to be picked up by kThread
	uThread* getWork();									//Get a unit of work from the ready queue
	uThread* getWorkOrWait();							//Get a unit of work or if not available sleep till there is one


};


#endif /* CLUSTER_H_ */