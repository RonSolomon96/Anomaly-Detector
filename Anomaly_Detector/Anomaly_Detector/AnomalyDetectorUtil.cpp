


#include "AnomalyDetectorUtil.h"
#include <iostream>
#include <vector>

float avg(std::vector<float>x, int size) {
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum += x[i];
	}
	return (sum/size);
}

// returns the variance of X and Y
float var(std::vector<float> x, int size) {
	float sum = 0, u;
	u = avg(x, size);
	for (int i = 0;i < size;i++) {
		sum = sum + (x[i] * x[i]);
	}
	float temp = (float)1.0 / (float)size;
	return ((temp * sum) - (u * u));
}

// returns the covariance of X and Y
float cov(std::vector<float> x, std::vector<float> y, int size) {
	float sumX = 0;
	float sumY = 0;
	float sumXY = 0;
	for (int i = 0; i < size; i++) {
		sumX += x[i];
		sumY += y[i];
		sumXY += x[i] * y[i];

	}
	sumX = sumX / size;
	sumY = sumY / size;
	sumXY = sumXY / size;
	return sumXY - (sumX * sumY);

}


// returns the Pearson correlation coefficient of X and Y
float pearson(std::vector<float> x, std::vector<float> y, int size) {
	float varX, varY, per;
	varX = sqrt(var(x, size));
	varY = sqrt(var(y, size));
	per = cov(x, y, size) / (varX * varY);
	return per;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {
	std::vector<float> x;
	std::vector<float> y;
	for (int i = 0;i < size;i++) {
		x.push_back(points[i]->x);
		y.push_back(points[i]->y);
	}
	float a = cov(x, y, size) / var(x, size);
	float b = avg(y, size) - a * (avg(x, size));

	return Line(a, b);
}
// returns the deviation between point p and the line equation of the points
float dev(Point p, Point** points, int size) {
	Line l = linear_reg(points, size);
	return dev(p, l);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
	float x = p.y - l.f(p.x);
	return std::abs(x);
}
