
#include<iostream>
#include<vector>
using namespace std;

class function_object{
    private:
        int num_parameters;
        vector<double> curr_parameter_value;

        // this is why we need the function so as to calculate dervative for any given parameter 
        // by using f'(x) = f(x+h)-f(x)/h and hence we will need to somehow pass f(x) here
        double derivative(){

        }
        
    public:
        // TODO: This constructor should be able to take in a function as an argument 
        //and count the number of arguments that functions has
        function_object(){
            // For development purpose we hardcode it here according to function() in main
            num_parameters = 2;

            // This will be the initial guessing of parameters for this another guessing generator will be designed
            curr_parameter_value.push_back(10);
            curr_parameter_value.push_back(10);
        }
};