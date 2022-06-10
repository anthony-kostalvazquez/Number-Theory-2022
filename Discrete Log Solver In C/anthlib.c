#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <flint/arith.h>
#include <flint/flint.h>
#include <flint/fmpz.h>
#include <flint/fmpz_mod.h>

//takes an integer n and return 1 if its a prime and 0 if it isnt
int brute_force_primality_test(int p)
{
    for(int i = 2; i <= ceil(sqrt(p)) ;i++)
    {
        if(p % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

//finds the inverse of a mod b using gmp library functions 
int gmp_inverse(int a, int mod_b)
{
    //Initialize (gmp needs string inputs)
    int n;
    char a_str[10000000];
    char mod_b_str[10000000];
    char a_inverse_str[10000000];

    int a_inverse_int;

    sprintf(a_str, "%d", a);
    sprintf(mod_b_str, "%d", mod_b);

    //initialize the inputs for the inverse function as mpz_t type
    mpz_t rop, op1, op2;
    mpz_init ( rop );
    mpz_init ( op1 );
    mpz_init ( op2 );

    //setting op1 and op2 to a and mod b
	mpz_set_str ( op1, a_str, 10 );
	mpz_set_str ( op2, mod_b_str, 10 );

    //calling the function to invert
    n = mpz_invert ( rop, op1, op2 );

    //turning the result into a base 10 str and storing in a_inverse_str
    mpz_get_str ( a_inverse_str, 10, rop );

    //printing out an error statement if the input values are not invertible
    if(n == 0)
    {
        printf("ERROR INVERSE DOES NOT EXIST");
    }

    //free the variables up
    mpz_clear ( rop );
    mpz_clear ( op1 );
    mpz_clear ( op2 );

    //return the inverse of a as an int
    return atoi(a_inverse_str) % mod_b;
}

//takes a,b,n as ulong and calculates x such that a^x = b mod n using a brute force technique 
//and many flint library functions and data types
unsigned long int brute_force_discrete_log(unsigned long int a, unsigned long int b, unsigned long int n)
{   
    unsigned long int x;
    unsigned long int increment = 1;
    //initializing into an fmpz data type & fmpz modular data type 
    fmpz_t n_fmpz , a_fmpz , b_fmpz, i_fmpz, temp; 

    //putting the input numbers into the fmpz data type & fmpz modular data type
    fmpz_init_set_ui(a_fmpz, a);
    fmpz_init_set_ui(b_fmpz, b);
    fmpz_init_set_ui(n_fmpz, n);

    //fmpz_mod_ctx_init (ctx, n_fmpz);

    for(fmpz_init(i_fmpz) ; 0 > fmpz_cmp(i_fmpz, n_fmpz) ;fmpz_add_ui(i_fmpz, i_fmpz, increment))
    {   
        //calcs a^i mod n and stores it in temp
        fmpz_powm(temp, a_fmpz, i_fmpz, n_fmpz);

        if(0 == fmpz_cmp(temp , b_fmpz))
        {
            x = fmpz_get_ui(i_fmpz);
            break;
        }
    }

    fmpz_clear ( a_fmpz );
    fmpz_clear ( b_fmpz );
    fmpz_clear ( i_fmpz );
    fmpz_clear ( n_fmpz );
    fmpz_clear ( temp );
    //fmpz_mod_ctx_clear(ctx);
    return x;
}

//Takes integers n,a,b and solves for x in the equation a^x = b (mod n)
//Using the famous baby-step giant-step algorithm then prints its answer and time
unsigned long int baby_step_giant_step_discrete_log (unsigned long int a, unsigned long int b, unsigned long int n)
{   
    //initialize
    unsigned long int x;
    int y;
    int giant_step_length;

    //initializing into an fmpz data type
    fmpz_t n_fmpz , a_fmpz , b_fmpz, m_fmpz, i_fmpz, m_fmpz_minus_one, giant_step, baby_step; 
    fmpz_mod_ctx_t mod_n;

    //putting the input numbers into the fmpz data type
    fmpz_init_set_ui(a_fmpz, a);
    fmpz_init_set_ui(b_fmpz, b);
    fmpz_init_set_ui(n_fmpz, n);

    fmpz_mod_ctx_init(mod_n, n_fmpz);

    //setting m_fmpz to the ceiling of the square root of n-1
    fmpz_sub_ui(m_fmpz, n_fmpz, 1);
    if(fmpz_is_square(m_fmpz) == 0)
    {
        fmpz_sqrt(m_fmpz, m_fmpz);
        fmpz_add_ui(m_fmpz, m_fmpz, 1);
    }
    else
    {
        fmpz_sqrt(m_fmpz, m_fmpz);
    }

    //----------GIANT STEP----------//
    fmpz_sub_ui(m_fmpz_minus_one, m_fmpz, 1);
    unsigned long int giant_step_array[fmpz_get_ui(m_fmpz_minus_one)];

    //this loop iterates from i = 0 to m-1
    for(fmpz_init(i_fmpz) ; 0 > fmpz_cmp(i_fmpz, m_fmpz_minus_one) ;fmpz_add_ui(i_fmpz, i_fmpz, 1))
    {   
        //calcs i*m and stores it in temp
        fmpz_mul(giant_step, i_fmpz, m_fmpz);

        //calcs a^im mod n and stores it in temp
        fmpz_mod_pow_fmpz(giant_step, a_fmpz, giant_step, mod_n);

        //calculates the inverse of a^im modulo n and puts it in temp
        fmpz_mod_inv(giant_step, giant_step, mod_n);

        //calculates b * a^(-im) modulo n and stores it in temp
        fmpz_mod_mul(giant_step, b_fmpz, giant_step, mod_n);

        //sets b * a^(-im) to the ith position of giant_step_array
        giant_step_array[fmpz_get_ui(i_fmpz)] = fmpz_get_ui(giant_step);
    }

    //gets the length of the array
    giant_step_length = (sizeof giant_step_array / sizeof giant_step_array[0]);

    //----------BABY STEP----------//
    for(unsigned long int i = 0; i < n; i++)
    {
        //calculates y = a^i mod n and store it in baby_step
        fmpz_mod_pow_ui(baby_step, a_fmpz, i, mod_n);

        //this loop looks for a collision within the giant_step_array
        for(unsigned long int j = 0; j < giant_step_length; j++)
        {
            if (fmpz_get_ui(baby_step) == giant_step_array[j])
            {
                x = j * fmpz_get_ui(m_fmpz) + i;

                //clearing all my fmpz_types
                fmpz_clear ( a_fmpz );
                fmpz_clear ( b_fmpz );
                fmpz_clear ( n_fmpz );
                fmpz_clear ( m_fmpz );
                fmpz_clear ( i_fmpz );
                fmpz_clear ( m_fmpz_minus_one );
                fmpz_clear ( baby_step );
                fmpz_clear ( giant_step );
                fmpz_mod_ctx_clear(mod_n);

                return x;
            }
        }

    }

    //clearing all the fmpz data types
    fmpz_clear ( a_fmpz );
    fmpz_clear ( b_fmpz );
    fmpz_clear ( n_fmpz );
    fmpz_clear ( m_fmpz );
    fmpz_clear ( i_fmpz );
    fmpz_clear ( m_fmpz_minus_one );
    fmpz_clear ( baby_step );
    fmpz_clear ( giant_step );
    fmpz_mod_ctx_clear(mod_n);
}