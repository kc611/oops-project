#include<iostream>
#include<vector>
using namespace std;

//Main running file in which entire project will be imported as header files/libraries
#include"curve_fitter_class.hpp"

double user_function(double x,double parameters[]){
    double a = parameters[0];double b = parameters[1];double c = parameters[2];double d = parameters[3];
    double y = a*x*x*x + b*x*x + c*x + d;
    return y;
}

int main(){

    // if we want to take input from file simple pass the filename to following constructor
    DataSet dataSet = DataSet(1);

    //curve fitter class constructor called and data points passed to it.
    Curve_fitter example_curve_fitter = Curve_fitter(dataSet);

    // arguments here are in order: function itself, number of parameters,number of iterations,h(for differentiation),rmse tolerance;
    example_curve_fitter.fit_curve(&user_function,4,5,0.0001,0.0005);

    cout<<endl;
    cout<<"DONE"<<endl;

}