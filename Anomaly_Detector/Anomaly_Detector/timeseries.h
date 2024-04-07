
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <fstream>
#include <iostream>
#include <vector>
#include<map>
using namespace std;

class TimeSeries {
private:
    const char* file_name;
    vector<string> features;
    vector<vector <float>> data;
    //map<string,vector<float>> myMap;

public:


    TimeSeries(const char* CSVfileName);

     vector<vector<float>> GetData() const;

     vector<string> GetFeatures()const ;

    int InsertData();


};



#endif /* TIMESERIES_H_ */