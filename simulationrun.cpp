/*--------------------/
ALH
Simulation RUN
/--------------------*/

#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <algorithm>
using namespace std;

double runTrial(int seed, double arrivalRate, double serviceRate, int numberOfServers, double maxSimTime, double warmup){
    int i;
    double outcome, r1, r2, serviceTime, serviceStartDate, serviceEndDate, wait;
    double sumWaits = 0.0, arrivalDate = 0.0;
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
        while (r1 == 0.0 || r2 == 0.0 || r1 == 1.0 || r2 == 1.0){
            r1 = ((double)rand() / (double)RAND_MAX);
            r2 = ((double)rand() / (double)RAND_MAX);
        }
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

    outcome = (sumWaits) / (waits.size());
    return outcome;
}

int main(int argc, char **argv){
    int i, seed;
    double solution;
    int numberOfServers = atoi(argv[1]);
    int numberOfTrials = atoi(argv[2]);
    double arrivalRate = atof(argv[3]);
    double serviceRate = atof(argv[4]);
    double maxSimTime = atof(argv[5]);
    double warmup = atof(argv[6]);
    double sumMeanWaits = 0.0;
    vector<double> meanWaits;

    time_t startTime, endTime;
    startTime = clock();

    for(seed = 0; seed < numberOfTrials; ++seed ){
        meanWaits.push_back(runTrial(seed, arrivalRate, serviceRate, numberOfServers, maxSimTime, warmup));
    }

    for(i = 0; i < meanWaits.size(); ++i){
        sumMeanWaits += meanWaits[i];
    }
    solution = (sumMeanWaits) / (meanWaits.size());

    endTime = clock();
    double totalTime = (((endTime - startTime) / double(CLOCKS_PER_SEC)) * 1000);
    cout << totalTime << endl;
}
