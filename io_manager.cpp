//Input Output Manager package where all input output related funtions will be defined
#include<iostream>
#include<vector>
#include <fstream>
using namespace std;

int data_from_txt_file(string filename,vector<double> &x_data,vector<double> &y_data){
    ifstream raw_data;
    raw_data.open(filename);
    if(!raw_data){
        cout<<"File does not exist or is corrupted"<<endl;
        return -1;
    }

    double x,y;
    // TODO:Add an error here if other than int found or more than two integers on same line
    while(raw_data>>x>>y) {
        x_data.push_back(x);
        y_data.push_back(y);
    }

    return x_data.size();
}