//Main running file in which entire project will be imported as header files/libraries
#include<iostream>
#include<vector>
#include "io_manager.cpp"
#include "curve_fitter_class.cpp"
using namespace std;

bool import_from_file = 1;
int data_size;

double user_function(double x,double parameters[]){
    double a = parameters[0];double b = parameters[1];double c = parameters[2];
    
    double y = a*x*x + b*x + c;
    return y;
}

int main(){

    vector<double> x_data_points,y_data_points;
    //write the points in the example.txt text file in the already written format: x y (without brackets or commas, single point on single line)
    if(import_from_file){
        data_size = data_from_txt_file("example.txt",x_data_points,y_data_points);
    }else{
        // User will Manually input data points here to be implemented later
    }


    // //curve fitter class constructor called and data points passed to it.
    curve_fitter example_curve_fitter = curve_fitter(data_size,x_data_points,y_data_points);

    // arguments here are in order: function itself, number of parameters,number of iterations,h(for differentiation)
    example_curve_fitter.fit_curve(&user_function,3,1,0.0001);

    cout<<"DONE"<<endl;

}