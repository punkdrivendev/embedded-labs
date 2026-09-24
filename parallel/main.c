
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "linmath.h"
#include <sys/time.h>


int N = 0;
int N2 = 0;
int N3 = 0;
/*
void fill_up(int *arr, int size);
void *func1(void *P);
void *func2(void *P);
void *func3(void *P);
int cmp(const void *a, const void *b);
void display(int *arr, int N);
*/

void fill_up(int *arr, int size){
    srand(time(NULL));
    for(int i = 0; i<size; i++){
        arr[i] = rand() % 10;
    }
}


int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    return (x > y) - (x < y);

}

void display(int *arr, int N){
    for(int i = 0; i<N; i++){
        printf(" %d ",arr[i]);
    }
    printf("\n");
}
void *func1(void *P){

    int *A = calloc(N,sizeof(int));
    int *B = calloc(N,sizeof(int));
    int *C = calloc(N,sizeof(int));
    int *MA = calloc((N*N),sizeof(int));
    int *ME = calloc((N*N),sizeof(int));

    fill_up(A,N);
    fill_up(B,N);
    fill_up(C,N);
    fill_up(MA,N*N);
    fill_up(ME,N*N);

    int *E = calloc(N,sizeof(int));
    int *arr_res = sq_matrix_mult(MA,ME,N);
    int *vec_x_arr = vector_x_matrix(C,arr_res,N);
    int *vec_sum1 = vec_sum(A,vec_x_arr, N);
    E = vec_sum(vec_sum1,B,N);
    free(arr_res);
    free(vec_x_arr);
    free(vec_sum1);

   // printf("%d,%d,%d\n",E[0],E[1],E[2]);
    free(E);

}

void *func2(void *P){
    int *MG = calloc((N2*N2),sizeof(int));
    int *MH = calloc((N2*N2),sizeof(int));
    int *MK = calloc((N2*N2),sizeof(int));
    int *ML = calloc((N2*N2),sizeof(int));

    fill_up(MG,N2*N2);
    fill_up(MH,N2*N2);
    fill_up(MK,N2*N2);
    fill_up(ML,N2*N2);

    int *MF = calloc(N2*N2, sizeof(int));
    int *mult_res = sq_matrix_mult(MH,MK,N2);
    int *trans1 = transpose_matrix(mult_res, N2);
    int *trans2 = transpose_matrix(ML, N2);
    int *sum_matrix = matrix_sum(MG,trans1,N2);
    MF = matrix_sub(sum_matrix, trans2, N2);
    free(mult_res);
    free(trans1);
    free(trans2);
    free(sum_matrix);
    qsort(MF,N2*N2,sizeof(int),cmp);
    //display(MF, N*N);
    free(MF);
}

void *func3(void *P) {
    int *MS = calloc((N3*N3),sizeof(int));
    int *MR = calloc((N3*N3),sizeof(int));
    int *MT = calloc((N3*N3),sizeof(int));

    fill_up(MS,N3*N3);
    fill_up(MR,N3*N3);
    fill_up(MT,N3*N3);

    int *res_mult = sq_matrix_mult(MR,MT,N3);
    qsort(MS, N3*N3,sizeof(int),cmp);
    int *sum_of_matrix = matrix_sum(res_mult, MS, N3);
    int result = max_matrix_elem(sum_of_matrix, N3);
    //printf("s: %d",result);
    free(res_mult);
    free(sum_of_matrix);
}


int main(){



    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    printf("Enter size of the first matrix: \n");
    scanf("%d", &N);
    printf("Enter size of the first matrix: \n");
    scanf("%d", &N2);
    printf("Enter size of the first matrix: \n");
    scanf("%d", &N3);
    printf("Filling up the matricies %d by %d \n", N, N);
    printf("Creating threads \n");

    struct timeval start,end;

    gettimeofday(&start, NULL);

    const int status_t1 = pthread_create(&thread1, NULL, func1, NULL);
    printf("Thread1 \n");
    const int status_t2 = pthread_create(&thread2, NULL, func2, NULL);
    printf("Thread2 \n");
    const int status_t3 = pthread_create(&thread3, NULL, func3, NULL);
    printf("Thread3 \n");
    if (status_t1 == 0){
        pthread_join(thread1, NULL);
        printf("Finished calculating func1 \n");
    }
    if(status_t2 == 0){
        pthread_join(thread2, NULL);
        printf("FInished calculating func2 \n");
    }
    if(status_t3 == 0){
        pthread_join(thread3, NULL);
        printf("Finished calculating func3 \n");
   }

    gettimeofday(&end, NULL);

    double time_elapsed = (end.tv_usec - start.tv_usec)/1000000.0 + (end.tv_sec - start.tv_sec);


    printf("Time used: %.6lf \n", time_elapsed);


    /*
    //func1
    int A[3]= {1,2,3};
    int B[3] = {4,5,6};
    int C[3] = {7,8,9};
    int MA[9] = {1,2,3,4,5,6,7,8,9};
    int ME[9] =  {1,2,3,4,5,6,7,8,9};
    //func2
    int MG[9] = {1,2,3,4,5,6,7,8,9};
    int MH[9] = {1,2,3,4,5,6,7,8,9};
    int MK[9] = {1,2,3,4,5,6,7,8,9};
    int ML[9] = {1,2,3,4,5,6,7,8,9};


    int MS[9] = {1,2,3,4,5,6,7,8,9};
    int MR[9] = {1,2,3,4,5,6,7,8,9};
    int MT[9] = {1,2,3,4,5,6,7,8,9};
    */

    return 0;
}
