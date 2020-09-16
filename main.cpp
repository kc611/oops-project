//Main running file in which entire project will be imported as header files/libraries
#include<iostream>
#include<vector>
#include "io_manager.cpp"
using namespace std;

int main(){
    vector<int> x_data_points,y_data_points;
    data_from_txt_file("example.txt",x_data_points,y_data_points);
    cout<<x_data_points[0]<<" "<<y_data_points[1]<<endl;
}