
double pow(double base,int exp){ 
    if( exp == 0){
        return 1;
    }

    double curr=pow(base, exp/2); 

    if(exp%2 == 0){
        return curr*curr; 
    }else{
        return base*curr*curr; 
    }
} 

class Matrix{
    private:
        double get_determinant(int size, double curr_matrix[][matrix_size]){
            double determinant=0;
            if(size==1){
                return curr_matrix[0][0];
            }
            double submat[matrix_size][matrix_size];
            if (size == 2){
                return ((curr_matrix[0][0] * curr_matrix[1][1]) - (curr_matrix[1][0] * curr_matrix[0][1]));
            }else{
                for (int c = 0; c < size; c++){
                    int subi = 0;
                    for (int i = 1; i < size; i++){
                        int subj = 0;
                        for (int j = 0; j < size; j++){
                            if (j == c)
                                continue;
                            submat[subi][subj] = curr_matrix[i][j];
                            subj++;
                        }
                        subi++;
                    }
                    determinant = determinant + (pow(-1, c) * curr_matrix[0][c] * get_determinant(size - 1, submat));
                }
            }
            return determinant;
        }

    public:
        double elements[matrix_size][matrix_size];
        int rows,columns;
        
        Matrix(){
            for(int i=0;i<matrix_size;i++){
                for(int j=0;j<matrix_size;j++){
                    elements[i][j]=0;
                }
            }
        }

        Matrix(int curr_row,int curr_columns){
            rows = curr_row;columns=curr_columns;
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

        Matrix operator*(Matrix const &other_matrix){
            Matrix result = Matrix(rows,other_matrix.columns);

            for(int i=0;i<result.rows;i++){
                for(int j=0;j<result.columns;j++){
                    for(int k=0;k<columns;k++){
                        result.elements[i][j] += elements[i][k] * other_matrix.elements[k][j];
                    }
                }
            }
            
            return result;
        }

        double determinant(){
            return get_determinant(rows,elements);
        }

        Matrix adjoint(){ 
            int size = rows;
            Matrix result = Matrix(size,size);
            if(size == 1){ 
                result.elements[0][0] = 1; 
                return result; 
            } 
            
            for (int i=0; i<size; i++) { 
                for (int j=0; j<size; j++) { 
                    Matrix cofactor = Matrix(size-1,size-1);
                    int iptr=0,jptr=0;      
                    for(int k=0;k<size;k++){
                        if(k==i){
                            continue;
                        }
                        jptr=0;
                        for(int l=0;l<size;l++){
                            if(l==j){
                                continue;
                            }
                            cofactor.elements[iptr][jptr]=elements[k][l];
                            jptr++;
                        }
                        
                        iptr++;
                    }
                    result.elements[j][i] = pow(-1, i+j) * cofactor.determinant(); 
                }
            } 
            return result;
        } 
  
        Matrix inverse(){
            int size = rows;
            Matrix result = adjoint();
            double curr_det = determinant();
            for(int i=0;i<result.rows;i++){
                for(int j=0;j<result.columns;j++){
                    result.elements[i][j] /= curr_det;
                }
            }
            return result;
        }

        void print(){
            for(int i=0;i<rows;i++){
                for(int j=0;j<rows;j++){
                    cout<<elements[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
};