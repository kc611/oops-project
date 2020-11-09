#include<iostream>
#include<vector>
#include<limits.h>
#include "matrix_class.cpp"
using namespace std;
#define matrix_size 100 // for some reason matrix size 1000 will not execute memory overflow perhaps



class curve_fitter{
    private:
        int num_data_points;
        int num_parameters;
        int num_iterations;

        double step_value;
        double (*curr_function)(double,double*);

        double residual_array[matrix_size];
        double x_data_points[matrix_size];
        double y_data_points[matrix_size];
        double parameters[matrix_size];

        Matrix jacobian_matrix;

        bool initialize_curve_fitter(){
            for(int i=0;i<matrix_size;i++){
                residual_array[i]=0;
                x_data_points[i]=0;
                y_data_points[i]=0;
                //sets initial guess between 0-10
                parameters[i]=i+1;
            }
            return 0;
        }

        bool show_graph(){
            return 0;
        }

        bool calc_residuals(){
            
            for(int i=0;i<num_data_points;i++){
                residual_array[i] = curr_function(x_data_points[i],parameters) - y_data_points[i];
            }

            return 0;
        }

        bool eval_jacobian(){
            for(int i=0;i<num_data_points;i++){
                double f_x = curr_function(x_data_points[i],parameters); 
                for(int j=0;j<num_parameters;j++){
                    parameters[j]+=step_value;
                    double f_x_h = curr_function(x_data_points[i],parameters);
                    parameters[j]-=step_value;
                    jacobian_matrix.elements[i][j]=f_x_h/step_value - f_x/step_value;
                    cout<<jacobian_matrix.elements[i][j]<< " ";
                }
                cout<<endl;
            }

            return 0;
        }

        bool update_parameters(){
            return 0;
        }

        bool update_graph(){
            return 0;
        }

    public:

        curve_fitter(int datapoints,vector<double> &x_data,vector<double> &y_data){
            num_data_points = datapoints;
            initialize_curve_fitter();
            for(int i=0;i<datapoints;i++){
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
                
                // calculate residual array ,residuals are calculated in array: residual_array[matrix_size]
                calc_residuals();

                // evaluate jacobian matrix ,jacobian matrix is stored in:  jacobian_matrix[matrix_size][matrix_size]
                // jacobian matrix transpose is stored in: jacobian_matrix_transpose[matrix_size][matrix_size]
                eval_jacobian();

                // update the parameters in function object
                update_parameters();

                // update graph optional
                update_graph(); 
            }

            // return 1 if opreation successful 0 if failed
            return 0;
        }

    

};