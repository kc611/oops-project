#include<iostream>
#include<vector>
#include<limits.h>
#include "function_class.cpp"
using namespace std;
#define matrix_size 1000

class curve_fitter{
    private:
        int num_data_points;
        int num_parameters;
        int num_iterations;
        double jacobian_matrix[matrix_size][matrix_size];
        double jacobian_matrix_transpose[matrix_size][matrix_size];
        double multi_matrix[matrix_size][matrix_size];
        double residual_array[matrix_size];
        double x_data_points[matrix_size];
        double y_data_points[matrix_size];
        double (*curr_function)(double,double*);
        double parameters[matrix_size];
        double step_value;

        bool initialize_curve_fitter(){
            for(int i=0;i<matrix_size;i++){
                residual_array[i]=0;
                x_data_points[i]=0;
                y_data_points[i]=0;
                for(int j=0;j<matrix_size;j++){
                    jacobian_matrix[i][j]=0;
                }
                parameters[i]=1;
            }
        }

        bool show_graph(){

        }

        bool calc_residuals(){
            for(int i=0;i<num_data_points;i++){
                residual_array[i] = curr_function(x_data_points[i],parameters) - y_data_points[i];
            }
        }

        bool eval_jacobian(){
            for(int i=0;i<num_data_points;i++){
                double f_x = curr_function(x_data_points[i],parameters); 
                for(int j=0;j<num_parameters;j++){
                    parameters[j]+=step_value;
                    double f_x_h = curr_function(x_data_points[i],parameters);
                    parameters[j]-=step_value;
                    jacobian_matrix[i][j]=f_x_h/step_value - f_x/step_value;
                    jacobian_matrix_transpose[j][i]=jacobian_matrix[i][j];
                }
            }

        }

        bool multiply_matrices(){
            for(int i=0;i<num_data_points;i++){
                for(int j=0;j<num_data_points;j++){
                    for(int k=0;k<num_parameters;k++){
                        multi_matrix[i][j]=jacobian_matrix[i][k]+jacobian_matrix_transpose[k][j];
                    }
                }
            }

            for(int i=0;i<num_data_points;i++){
                for(int j=0;j<num_data_points;j++){
                    cout<<multi_matrix[i][j]<<" ";
                }
            }
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
        bool fit_curve(double (*function)(double,double*),int number_of_parameters,int number_of_iterations,double step){
            // create a function ibject and assign it to curr function
            curr_function = function;
            step_value = step;
            num_parameters = number_of_parameters;
            num_iterations = number_of_iterations;
            // This is optional
            show_graph();

            for(int i=1;i<=number_of_iterations;i++){
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