#include "TimeSeries.h"
#include <string>
#include <sstream>
TimeSeries::TimeSeries(const char* CSVfileName) :file_name(CSVfileName) {

    InsertData();

}

int TimeSeries::InsertData() {
    ifstream file(this->file_name);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return -1;
    }

    // Read the file line by line
    string line;

    getline(file, line);
    // Create a stringstream from the line
    stringstream ss(line);

    // Read each field from the stringstream, separated by comma
    string field;
    while (getline(ss, field, ',')) {
        this->features.push_back(field);
        vector<float>v;
        this->data.push_back(v);
    }
    while (getline(file, line)) {
        // Create a stringstream from the line
        stringstream ss(line);
        int counter = 0;
        while (getline(ss, field, ',')) {
            this->data[counter].push_back(stof(field));
            counter++;
            counter = counter % 4;
        }
    }
}

     vector<vector<float>> TimeSeries:: GetData()const  {
        return this->data;
    }

     vector<string> TimeSeries::GetFeatures() const {
         return this->features;

     }
  