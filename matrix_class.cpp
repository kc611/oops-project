#define matrix_size 100 // for some reason matrix size 1000 will not execute memory overflow perhaps

class Matrix{
    public:
        double elements[matrix_size][matrix_size];
        int rows,columns;

        Matrix(int curr_row,int curr_columns){
            rows = curr_row;columns=curr_columns;
            initialize_matrix();
        }

        Matrix(){
            initialize_matrix();
        }

        void initialize_matrix(){
            for(int i=0;i<matrix_size;i++){
                for(int j=0;j<matrix_size;j++){
                    elements[i][j]=0;
                }
            }
        }

        Matrix transpose(){
            Matrix transpose_mat = Matrix(columns,rows);
            for(int i=0;i<columns;i++){
                for(int j=0;j<rows;j++){
                    transpose_mat.elements[i][j] = elements[j][i];
                }
            }
            return transpose_mat;
        }

        Matrix multiply_with(Matrix other_matrix){
            Matrix result = Matrix();
            result.rows = rows;
            result.columns = other_matrix.columns;
            for(int i=0;i<result.rows;i++){
                for(int j=0;j<result.columns;j++){
                    for(int k=0;k<columns;k++){
                        result.elements[i][j] += elements[i][k] * other_matrix.elements[k][j];
                    }
                }
            }
        }

        // double get_determinant(int curr_size,double curr_matrix[][matrix_size]){
        //     double curr_determinanat = 0;
        //     if(curr_size==1){
        //         return curr_matrix[0][0];
        //     }
        //     for(int i=0;i<curr_size;i++){
        //         double curr_element = curr_matrix[i][0];
        //         double child_matrix[matrix_size][matrix_size];
        //         int kpointer=0,jpointer=0;
        //         for(int j=0;j<curr_size;j++){
        //             if(j==i){
        //                     continue;
        //             }
        //             for(int k=0;k<curr_size;k++){
        //                 if(k==i){
        //                     continue;
        //                 }
        //                 child_matrix[jpointer][kpointer]=curr_matrix[j][k];kpointer++;
        //             }
        //             jpointer++;
        //         }
        //         curr_determinanat+=curr_element*get_determinant(curr_size-1,child_matrix);
        //     }    
        //     return curr_determinanat;
        // }

};