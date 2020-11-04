//Main running file in which entire project will be imported as header files/libraries
#include<iostream>
#include<vector>
#include "io_manager.cpp"
#include "curve_fitter_class.cpp"
using namespace std;

bool import_from_file = 0;
int data_size;

double user_function(double x,double parameters[]){
    double a = parameters[0];double b = parameters[1];

    double y = a*x+b;
    
    return y;
}

int main(){

    double x_data_points[5] = {1,2,3,4,5},y_data_points[5] = {1,2,3,4,5};
    //choose if user wants to import from data file or terminal
    if(import_from_file){
        //this is working just needs some final touches
        //data_size = data_from_txt_file("example.txt",x_data_points,y_data_points);
    }else{
        // User will Manually input data points here

        // this one is for development
        data_size = 5;
        
        // datapoints are (1,1),(2,2)... and equation is of form ax+b so our final output should give a=1 and b=0
    }

    // //curve fitter class constructor called and data points passed to it.
    curve_fitter example_curve_fitter = curve_fitter(5,x_data_points,y_data_points);

    example_curve_fitter.fit_curve(&user_function,2,1,0.0001);

    // cout<<"DONE"<<endl;

}