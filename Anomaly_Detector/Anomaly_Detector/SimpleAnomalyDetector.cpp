#include "SimpleAnomalyDetector.h"
#include "AnomalyDetectorUtil.h"

AnomalyDetector::AnomalyDetector() {}

AnomalyDetector::~AnomalyDetector() {}



void AnomalyDetector::learn(const TimeSeries& ts) {


	vector<string> features = ts.GetFeatures();
	vector<vector<float>> d = ts.GetData();
	int num_of_features = features.size();

	for (int i = 0; i < num_of_features; i++) {
		float max_correlated = 0;
		string max_correlrate_name;
		int max_co_index = 0; 

 		for (int j = i; j < num_of_features; j++) {
			if (i != j) {
				float p = pearson(d[i], d[j], d[i].size());
				if (p > max_correlated) {
					max_correlated = p;
					max_correlrate_name = features[j];
					max_co_index = j;

				}
			}
		}
		vector<Point*> points;
		for (int z = 0; z < ts.GetData()[i].size(); z++) {

			points.push_back(new Point(d[i][z], d[max_co_index][z]));
		}
		Line l = linear_reg(points.data(), d[i].size());
		//find threshold

		float max = 0;
		for (int z = 0;z < points.size();z++) {
			float da = abs(points[z]->y - l.f(points[z]->x));
			if (da > max)
				max = da;
	
		}

		struct correlatedFeatures c = { features[i],features[max_co_index],i,max_co_index,max_correlated,l,
			max*1.1 };
		if (max_correlated >= 0.9) {
			this->cf.push_back(c);
		}
	}
}


vector<AnomalyReport> AnomalyDetector::detect(const TimeSeries& ts) {
	vector<string> features = ts.GetFeatures();
	vector<vector<float>> d = ts.GetData();
	int num_of_features = features.size();
	vector<AnomalyReport> v;
	for (correlatedFeatures c : this->cf) {
		vector<float> x = ts.GetData()[c.index1];
		vector<float> y = ts.GetData()[c.index2];
		for (size_t i = 0;i < x.size();i++) {
			if (isAnomaly(x[i], y[i], c)) {
				string d = c.feature1 + "-" + c.feature2;
				v.push_back(AnomalyReport(d, (i + 1)));
			}
		}

	}
	return v;
	
}
bool AnomalyDetector::isAnomaly(float x, float y, correlatedFeatures c) {
	return (abs(y - c.lin_reg.f(x)) > c.threshold);
}

