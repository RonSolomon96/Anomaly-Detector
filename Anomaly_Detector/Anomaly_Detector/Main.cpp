

#include <iostream>
#include <vector>
#include "AnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <cstring>


using namespace std;



void generateResult(char* msg) {
	ofstream out("result.txt");
			out << msg << endl;
	out.close();
}



int main() {
	ofstream out("result.txt");
	TimeSeries ts("train.csv");
	AnomalyDetector ad;
	ad.learn(ts);
	vector<correlatedFeatures> cf = ad.getNormalModel();

	TimeSeries ts2("test.csv");
	vector<AnomalyReport> r = ad.detect(ts2);

	for (AnomalyReport msg : r) {
		cout << msg.timeStep << endl;
		cout << msg.description << endl;
		out << msg.timeStep << endl;
		out << msg.description << endl;
	}
	cout << "done" << endl;
	return 0;
}
