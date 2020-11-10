#include<iostream>
#include<vector>
#include<math.h>
#include <iomanip>   
using namespace std;

#define matrix_size 100 // for some reason matrix size 1000 will not execute memory overflow perhaps

class Matrix{
    private:
        double determinant;

        double get_determinant(int size, double curr_matrix[][matrix_size]){
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
        

        Matrix(int curr_row,int curr_columns){
            rows = curr_row;columns=curr_columns;
            make_zero();
        }

        Matrix(){
            make_zero();
        }

        void make_zero(){
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
            return result;
        }

        double square_deteminant(){
            determinant=0;
            return get_determinant(rows,elements);
        }

        Matrix square_adjoint(){ 
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
                    result.elements[j][i] = pow(-1, i+j) * cofactor.square_deteminant(); 
                }
            } 
            return result;
        } 
  
        Matrix inverse(){
            int size = rows;
            Matrix result = square_adjoint();
            double curr_det = square_deteminant();
            for(int i=0;i<result.rows;i++){
                for(int j=0;j<result.columns;j++){
                    result.elements[i][j] /= curr_det;
                }
            }

            return result;
        }
};