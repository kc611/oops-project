#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;
#define matrix_size 100 // for some reason matrix size 1000 will not execute memory overflow perhaps

class curve_fitter{
    private:
        int num_data_points;
        int num_parameters;
        int num_iterations;
        double jacobian_matrix[matrix_size][matrix_size];
        double jacobian_matrix_transpose[matrix_size][matrix_size];
        double multi_matrix[matrix_size][matrix_size];
        double inverse_matrix[matrix_size][matrix_size];
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
                    multi_matrix[i][j]=0;
                    jacobian_matrix_transpose[i][j]=0;
                    inverse_matrix[i][j]=0;
                }
                parameters[i]=1;
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
                    jacobian_matrix[i][j]=f_x_h/step_value - f_x/step_value;
                    jacobian_matrix_transpose[j][i]=jacobian_matrix[i][j];
                }
            }
            return 0;

        }

        bool multiply_matrices(){
            for(int i=0;i<num_data_points;i++){
                for(int j=0;j<num_data_points;j++){
                    for(int k=0;k<num_parameters;k++){
                        multi_matrix[i][j]+=jacobian_matrix[i][k]*jacobian_matrix_transpose[k][j];
                    }
                }
            }

            return 0;
        }

        double get_determinant(int curr_size,double curr_matrix[][matrix_size]){
            double curr_determinanat = 0;
            if(curr_size==1){
                return curr_matrix[0][0];
            }
            for(int i=0;i<curr_size;i++){
                double curr_element = curr_matrix[i][0];
                double child_matrix[matrix_size][matrix_size];
                int kpointer=0,jpointer=0;
                for(int j=0;j<curr_size;j++){
                    if(j==i){
                            continue;
                    }
                    for(int k=0;k<curr_size;k++){
                        if(k==i){
                            continue;
                        }
                        child_matrix[jpointer][kpointer]=curr_matrix[j][k];kpointer++;
                    }
                    jpointer++;
                }
                curr_determinanat+=curr_element*get_determinant(curr_size-1,child_matrix);
            }    
            return curr_determinanat;
        }

        double* get_adjoint(int curr_size,double curr_matrix[matrix_size][matrix_size]){

        }

        bool calculate_inverse(){
            double determinant = get_determinant(num_data_points,multi_matrix);
            double *adjoint = get_adjoint(num_data_points,multi_matrix);
	        cout<<determinant<<endl;
            // for(int i=0;i<num_data_points;i++){
            //     for(int j=0;j<num_data_points;j++){
            //         cout<<inverse_matrix[i][j]<<" ";
            //     }
            //     cout<<endl;
            // }
            return 0;
        }

        bool update_parameters(){
            multiply_matrices();
            calculate_inverse();

            return 0;
        }

        bool update_graph(){
            return 0;
        }
    public:
        // This constructor would take argument as data points and assign default value to matrix and residuals
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
            return 0;
        }

    

};