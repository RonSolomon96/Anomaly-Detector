#include "SimpleAnomalyDetector.h"
#include "anomaly_detector_util.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}




void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
	
	
	vector<string> features = ts.GetFeatures();
	vector<vector<float>> d = ts.GetData();
	int num_of_features = features.size();
	//struct correlatedFeatures cf1 {"1","1",1,"1",1 };
	//cf1.threshehold = 1 

	for (int i = 0; i < num_of_features; i++) {
		int max_correlated = 0;
		string max_correlrate_name;
		int max_co_index = 0;
		for (int j = 0; j < num_of_features; j++) {
			if (i != j) {
				int p = pearson(d[i], d[j], d[i].size());
				if (p > max_correlated) {
					max_correlated = p;
					max_correlrate_name = features[j];
					max_co_index = j;

				}
			}
		}
		vector<Point*> points;
		for (int z; z < ts.GetData()[i].size(); z++) {

			points.push_back(new Point(d[i][z], d[max_co_index][z]));
		}

		

		struct correlatedFeatures c = { features[i],features[max_co_index],max_correlated,linear_reg(points.data(), d[i].size()),
			0.9 };
			
		this->cf.push_back(c);


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts) {
	// TODO Auto-generated destructor stub
}

