class Curve_fitter{
    private:
        int num_data_points;
        int num_parameters;
        int num_iterations;

        double step_value;
        double (*curr_function)(double,double*);

        Matrix jacobian_matrix;
        Matrix residual_array;

        DataSet curr_dataset;

        bool initialize_curve_fitter(){
            for(int i=0;i<matrix_size;i++){
                //sets initial guess for parameters between 0-10
                parameters[i]=rand()%10;
            }
            return 0;
        }

        bool calc_residuals(){
            for(int i=0;i<num_data_points;i++){
                residual_array.elements[i][0] = curr_function(curr_dataset.points[i].x,parameters) - 
                            curr_dataset.points[i].y;
            }
            return 0;
        }

        bool eval_jacobian(){
            for(int i=0;i<num_data_points;i++){
                double f_x = curr_function(curr_dataset.points[i].x,parameters); 
                for(int j=0;j<num_parameters;j++){
                    parameters[j]+=step_value;
                    double f_x_h = curr_function(curr_dataset.points[i].x,parameters);
                    parameters[j]-=step_value;
                    jacobian_matrix.elements[i][j]=f_x_h/step_value - f_x/step_value;
                }
            }
            return 0;
        }

        bool update_parameters(Matrix residual_diff){
            for(int i=0;i<num_parameters;i++){
                parameters[i]-=residual_diff.elements[i][0];
            }
            return 0;
        }

        double calculate_rmse(){
            double curr_rmse = 0;
            for(int i=0;i<num_data_points;i++){
                double temp;
                temp= (curr_dataset.points[i].y - curr_function(curr_dataset.points[i].x,parameters));
                curr_rmse+= temp*temp;
            }
            return curr_rmse;
        }

    public:
        double parameters[matrix_size];

        Curve_fitter(DataSet dataset){
            num_data_points = dataset.num_datapoints;
            curr_dataset = dataset;
        }

        // This must take in function as an argument (function() from main in this case) and create a function object from it
        bool fit_curve(double (*function)(double,double*),int number_of_parameters,int number_of_iterations,double step,double tolerance){
            initialize_curve_fitter();

            // takes a function pointer and assigns it to curr function
            curr_function = function;
            step_value = step;
            num_parameters = number_of_parameters;
            num_iterations = number_of_iterations;

            residual_array.rows = num_parameters;residual_array.columns = 1;
            jacobian_matrix.rows = num_data_points;jacobian_matrix.columns = num_parameters;

            bool flag=0;

            cout<<"Initial Guess : "<<endl;
            for(int i=0;i<num_parameters;i++){
                cout<<"Parameter "<<i+1<<" : "<<parameters[i]<<endl;
            }
            cout<<endl;
            for(int i=1;i<=number_of_iterations;i++){
                //for i'th iteration
                
                // calculate residual array ,residuals are calculated in array: residual_array[matrix_size]
                calc_residuals();

                // evaluate jacobian matrix ,jacobian matrix is stored in:  jacobian_matrix[matrix_size][matrix_size]
                // jacobian matrix transpose is stored in: jacobian_matrix_transpose[matrix_size][matrix_size]
                eval_jacobian();

                // Solving the equations to calculate residual amount
                Matrix inverted = (jacobian_matrix.transpose() * jacobian_matrix).inverse();
                Matrix pseudo_inv = inverted * jacobian_matrix.transpose();
                Matrix residual_diff = pseudo_inv * residual_array;

                //updating parameters according to residuals
                update_parameters(residual_diff);

                // calculating least square error
                double current_error = calculate_rmse();

                cout<<"Round "<<(i)<<" : Root Mean Squared Error : "<<current_error<<endl;
                for(int i=0;i<num_parameters;i++){
                    cout<<"Parameter "<<i+1<<" : "<<parameters[i]<<endl;
                }
                cout<<endl;
                // if error less than tolerance then break the loop
                if(current_error<tolerance){
                    flag=1;
                    break;
                }
            }

            if(flag==1){
                printf("Sucessfully converged the function upon the data points\n");
            }else{
                printf("Max number of iterations reached\n");
            }

            // return 1 if opreation successful 0 if failed
            return flag;
        }
};