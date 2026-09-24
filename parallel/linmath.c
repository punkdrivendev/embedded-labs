
#include <stdlib.h>
#include <stdio.h>
#include "linmath.h"

int *sq_matrix_mult(int *matrix1, int *matrix2, int N){
    
    int *res_matrix = malloc((N*N)*sizeof(int));
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N;j++){
                int temp = 0;
                for (int z = 0; z < N; z++){
                    temp += matrix1[N*i+z] * matrix2[N*z+j];
                }
                res_matrix[N*i+j] = temp;
            }
        }

    return res_matrix;
}

int *vector_x_matrix(int *vector1, int *matrix1, int N){
    
    int *res_vector = malloc(N*sizeof(int));
    int temp = 0;
    for(int j = 0; j<N; j++){
        for(int i = 0; i<N; i++){
            temp = 0;
            for(int r = 0; r<N; r++){
                temp += matrix1[N*r+j] * vector1[r];
            }
            res_vector[j] = temp;
        }
    }

    return res_vector;
}

int *transpose_matrix(int *matrix1, int N){

    int *res_matrix = malloc((N*N) * sizeof(int));
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            res_matrix[N*j+i] = matrix1[N*i+j];
        }
    }

    return res_matrix;
}

int max_matrix_elem(int *matrix1, int N){

    int max = matrix1[0];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(max < matrix1[N*i+j]){
                max = matrix1[N*i+j];
            }
        }
    }
    return max;
}

int *vec_sum(int *vec1, int *vec2, int N){
    int *res_vec = calloc(N,sizeof(int));
    for(int i = 0; i<N; i++){
        res_vec[i] = vec1[i] + vec2[i];
    }
    return res_vec;
}

int *matrix_sum(int *matrix1, int *matrix2, int N){

    int *res_matrix = calloc(N*N,sizeof(int));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            res_matrix[N*i+j] = matrix1[N*i+j] + matrix2[N*i+j];
        }
    }
    return res_matrix;
}

int *matrix_sub(int *matrix1, int *matrix2, int N){

    int *res_matrix = calloc(N*N,sizeof(int));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            res_matrix[N*i+j] = matrix1[N*i+j] - matrix2[N*i+j];
        }
    }
    return res_matrix;
}
