#include<iostream>
#include<vector>
#include<limits.h>
#include "function_class.cpp"
using namespace std;
#define matrix_size 1000

class curve_fitter{
    private:
        int num_data_points;
        double jacobian_matrix[matrix_size][matrix_size];
        double residual_array[matrix_size];
        double x_data_points[matrix_size];
        double y_data_points[matrix_size];
        function_object curr_function;

        bool initialize_curve_fitter(){
            for(int i=0;i<matrix_size;i++){
                residual_array[i]=0;
                x_data_points[i]=0;
                y_data_points[i]=0;
                for(int j=0;j<matrix_size;j++){
                    jacobian_matrix[i][j]=0;
                }
            }
        }

        bool show_graph(){

        }

        bool calc_residuals(){

        }

        bool eval_jacobian(){

        }

        bool update_parameters(){

        }

        bool update_graph(){

        }
    public:
        // This constructor would take argument as data points and assign default value to matrix and residuals
        curve_fitter(vector<double> x_data,vector<double> y_data){

            if(x_data.size()!=y_data.size()){
                //Invalid data error
            }else{
                num_data_points = x_data.size();
            }

            initialize_curve_fitter();

            for(int i=0;i<x_data.size();i++){
                x_data_points[i] = x_data[i];
                y_data_points[i] = y_data[i];
            }
            
        }

        // This must take in function as an argument (function() from main in this case) and create a function object from it
        bool fit_curve(int number_of_interations){
            // create a function ibject and assign it to curr function

            // This is optional
            show_graph();

            for(int i=1;i<=number_of_interations;i++){
                //for i'th iteration

                // calculate residual array
                calc_residuals();

                // evaluate jacobian matrix
                eval_jacobian();

                // update the paramets in function object
                update_parameters();

                // update graph optional
                update_graph(); 
            }

            // return 1 if opreation successful 0 if failed
        }

    

};