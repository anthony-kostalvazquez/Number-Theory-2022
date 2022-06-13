//This is a code that times the famous baby-step giant-step algorithm 
//versus a brute force algorithm

//The goal of these algs is to find an integer x such that a^x = b (mod n)
//a is a generator of the group
//b is an element mod n (0,1,....,n-1)

/*
###################FUN###################
#              Try To Input             #     
#             n = 77711                 #
#             a = 175                   #
#             b = 63368                 #
###################FUN###################
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <flint/arith.h>
#include <flint/flint.h>
#include <flint/fmpz.h>
#include "anthlib.h"
#include "omp.h"


int main()
{   
    
    //initialize
    unsigned long int n;
    unsigned long int a;
    unsigned long int b;
    unsigned long int x;

    double brute_time;
    double bsgs_time;
    double bsgsp_time;

    clock_t begin1, end1, begin2, end2, begin3, end3;

    //printing a statement to tell the user what the code does
    printf("\nWelcome, lets solve the problem a^x = b (mod n)");

    //Inputs
    do
    {
        printf("\nEnter a prime n: ");
        scanf(" %ld", &n);
    } 
    while (brute_force_primality_test(n) != 1);

    printf("Enter an integer a: ");
    scanf("%ld", &a);

    printf("Enter an integer b: ");
    scanf("%ld", &b);

    //formating inputs
    a = a % n;
    b = b % n;

    //solving a^x = b (mod n) using brute force and timing it
    
    begin1 = clock();

    x = brute_force_discrete_log(a , b , n);

    end1 = clock();
    brute_time = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("\nBrute Force Algorithm time: %lf Seconds", brute_time);
    printf("\nAnd Got the Solution %ld ^ %ld = %ld (mod%ld) \n", a, x, b, n);

    //solving a^x = b (mod n) using the baby step giant step algorithm and timing it
    begin2 = clock();

    x = baby_step_giant_step_discrete_log (a, b, n);
    
    end2 = clock();
    bsgs_time = (double)(end2 - begin2) / CLOCKS_PER_SEC;

    printf("\nBaby Step Giant Step Algorithm time: %lf Seconds", bsgs_time);
    printf("\nAnd Got the Solution %ld ^ %ld = %ld (mod%ld)\n", a, x, b, n);

    //solving a^x = b (mod n) using a parallel baby step giant step algorithm and timing it
    begin3 = clock();

    x = baby_step_giant_step_parallel(a, b, n);
    
    end3 = clock();
    bsgsp_time = (double)(end3 - begin3) / CLOCKS_PER_SEC;

    printf("\nParallel Baby Step Giant Step Algorithm time: %lf Seconds", bsgsp_time);
    printf("\nAnd Got the Solution %ld ^ %ld = %ld (mod%ld)\n", a, x, b, n);
}