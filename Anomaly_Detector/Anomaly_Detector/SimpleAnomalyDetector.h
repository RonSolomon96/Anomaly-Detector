
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "AnomalyDetectorUtil.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures {
	string feature1, feature2;  // names of the correlated features
	int index1, index2;
	float corrlation;
	Line lin_reg;
	float threshold;
};


class AnomalyDetector :public TimeSeriesAnomalyDetector {
	vector<correlatedFeatures> cf;
public:
	AnomalyDetector();
	virtual ~AnomalyDetector();

	virtual void learn(const TimeSeries& ts);
	bool isAnomaly(float x, float y, correlatedFeatures c);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel() {
		return cf;
	}

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */