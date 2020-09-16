//Input Output Manager package where all input output related funtions will be defined
#include<iostream>
#include<vector>
#include <fstream>
using namespace std;

bool data_from_txt_file(string filename,vector<int> &x_data,vector<int> &y_data){
    ifstream raw_data;
    raw_data.open(filename);
    if(!raw_data){
        cout<<"File does not exist or is corrupted"<<endl;
        return 0;
    }

    int x,y;
    // TODO:Add an error here if other than int found or more than two integers on same line
    while(raw_data>>x>>y) {
        x_data.push_back(x);
        y_data.push_back(y);
    }

    return 1;
}

//Use only for testing and development not in main runs

// int main(){
//     vector<int> a,b;
//     bool sucess = data_from_txt_file("example.txt",a,b);
//     cout<<sucess<<endl;
//     cout<<a[0]<<endl;
//     cout<<b[1]<<endl;
// }