#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct{
    double a;
    double a_squared;
    double numerator1;
    double numerator2;
    double denumerator1;
    double denumerator2;
    double invert;
    double temp1;
    double temp2;
    double temp3;
    double temp4;
    double result;
    int error;
}Data;


void *to_square(void *arg){

    Data *data = (Data *)arg;
    data->a_squared = data->a * data->a;

    return NULL;
}

void *calc_numerator1(void *arg){

    Data *data = (Data *)arg;

    data->numerator1 = 1+data->a+data->a_squared;

    return NULL;
}

void *calc_numerator2(void *arg){

    Data *data = (Data *)arg;

    data->numerator2 = 1-data->a+data->a_squared;

    return NULL;

}

void *calc_var_outside(void *arg){

    Data *data = (Data *)arg;

    data->temp1 = 5-2*data->a_squared;

    return NULL;

}

void *calc_denumerator1(void *arg){

    Data *data = (Data *)arg;

    data->denumerator1 = 2*data->a + data->a_squared;
    if(data->denumerator1 == 0){
        perror("denumerator1 is 0, exiting");
        data->error = 1;
    }
    return NULL;

}

void *calc_denumerator2(void *arg){

    Data *data = (Data *)arg;

    data->denumerator2 = 2*data->a - data->a_squared;
    if(data->denumerator2 == 0){
        perror("denumerator2 is 0, exiting");
        data->error = 1;
    }
    return NULL;

}

void *calc_num1_by_denum1(void *arg){

    Data *data = (Data *)arg;

    data->temp2 = data->numerator1 / data->denumerator1;

    return NULL;

}

void *calc_num2_by_denum2(void *arg){

    Data *data = (Data *)arg;

    data->temp3 = data->numerator2 / data->denumerator2;

    return NULL;

}
void *operation9(void *arg){

    Data *data = (Data *)arg;

    data->temp4 = data->temp2 + 2;

    return NULL;

}
void *operation10(void *arg){

    Data *data = (Data *)arg;

    data->temp4 = data->temp4 - data->temp3;

    return NULL;

}

void *to_invert(void *arg){

    Data *data = (Data *)arg;

    data->invert = 1/data->temp4;

    return NULL;

}

void *final_operation(void *arg){

    Data *data = (Data *)arg;

    data->result = data->invert * data->temp1;

    return NULL;

}

void display(double arg){

    printf("Result %lf\n", arg);

}

void user_input(double *arg){

    scanf("%lf", arg);

}

void func1(){

    Data *data = calloc(1, sizeof(Data));
    pthread_t t1,t2,t3;
    printf("Enter A:");
    user_input(&data->a);
    pthread_create(&t1, NULL, to_square,data);
    //calculate a to square
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, calc_numerator1, data);
    pthread_create(&t3, NULL, calc_numerator2, data);
    pthread_create(&t1, NULL, calc_var_outside, data);
    //calculating numerators 1 and 2 and outside thing 5-2a^2
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t1, NULL);

    //calculating denumerators 1 and 2
    pthread_create(&t1, NULL, calc_denumerator1,data);
    pthread_create(&t2, NULL, calc_denumerator2, data);

    pthread_join(t1, NULL);
    if(data->error == 1){
        printf("Calculation error");
        return ;
    }
    pthread_join(t2, NULL);
    if(data->error == 1){
        printf("Calculation error");
        return ;
    }

    //calculating numerator 1 divided by denumerator 1 and same with num2 and denum2
    pthread_create(&t1, NULL, calc_num1_by_denum1, data);
    pthread_create(&t2, NULL, calc_num2_by_denum2, data);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    //calculating num1_by_denum1 + 2
    pthread_create(&t1, NULL, operation9, data);

    pthread_join(t1,NULL);

    //calculating result of operation 9 - num2_by_denum2
    pthread_create(&t1, NULL, operation10, data);

    pthread_join(t1, NULL);
    //to -1
    pthread_create(&t1, NULL, to_invert, data);

    pthread_join(t1, NULL);
    // result multiplied by var_outside result
    pthread_create(&t1, NULL, final_operation, data);

    pthread_join(t1, NULL);

    display(data->result);

    free(data);
}
void func2(){
    Data *data = calloc(1, sizeof(Data));
    printf("\nNow for second function: ");
    user_input(&data->a);
    to_square(data);
    data->result = (4 - data->a_squared) / 2;
    display(data->result);
    free(data);
}
int main(){

    func1();
    func2();
    return 0;
}
