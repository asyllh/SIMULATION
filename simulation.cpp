/*--------------------/
ALH
Simulation C++ program for Geraint Palmer
Start date 02/07/2017
/--------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <cmath>
#include <queue>
#include <limits.h>
#include <algorithm>
#include <iomanip> //header providing parametric manipulators
using namespace std;

double runTrial(int seed, double arrivalRate, double serviceRate, int numberOfServers, double maxSimTime, double warmup){
	int i;
	double outcome;
	double sumWaits = 0.0;
	double r1, r2;
	double arrivalDate = 0.0;
	double serviceTime;
	double serviceStartDate;
	double serviceEndDate;
	double wait;
	vector<double> serversEnd;
	vector<double> temp;
	vector<double> waits;
	vector<vector<double> > records;
	srand(seed);

	for(i = 0; i < numberOfServers; ++i){
		serversEnd.push_back(0);
	}

	while(arrivalDate < maxSimTime){
		r1 = ((double)rand() / (double)RAND_MAX);
		r2 = ((double)rand() / (double)RAND_MAX);

		arrivalDate += (-log(r1))/arrivalRate;
		serviceTime = (-log(r2))/serviceRate;

		serviceStartDate = max(arrivalDate, (*min_element(serversEnd.begin(), serversEnd.end())));

		serviceEndDate = serviceStartDate + serviceTime;

		wait = serviceStartDate - arrivalDate;

		serversEnd.push_back(serviceEndDate);

		serversEnd.erase(min_element(serversEnd.begin(), serversEnd.end()));

		temp.push_back(arrivalDate);
		temp.push_back(wait);
		records.push_back(temp);
		temp.clear();

	}

	for(i = 0; i < records.size(); ++i){
		if(records[i][0] > warmup){
			waits.push_back(records[i][1]);
		}
	}

	for(i = 0; i < waits.size(); ++i){
		sumWaits += waits[i];
	}

	outcome = sumWaits/waits.size();

	return outcome;


}



int main(){


	int i;
	double solution;
	int numberOfServers = 3;
	int numberOfTrials = 20;
	double arrivalRate = 10.0;
	double serviceRate = 4.0;
	double maxSimTime = 800.0;
	double warmup = 100.0;
	double sumMeanWaits = 0.0;
	int seed;
	vector<int> meanWaits;

	time_t startTime, endTime;
	startTime = clock();

	for(seed = 0; seed < numberOfTrials; ++seed ){
		meanWaits.push_back(runTrial(seed, arrivalRate, serviceRate, numberOfServers, maxSimTime, warmup));
	}

	for(i = 0; i < meanWaits.size(); ++i){
		sumMeanWaits += meanWaits[i];
	}

	solution = sumMeanWaits/meanWaits.size();

	cout << "Solution: " << solution << endl;


	endTime = clock();
	int totalTime = (int)(((endTime - startTime) / double(CLOCKS_PER_SEC)) * 100);
	cout << "CPU Time = " << totalTime << " milliseconds.\n";

}