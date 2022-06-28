#include <stdio.h>
#include <flint/flint.h>
#include <gmp.h>
#include <flint/fmpz.h>
#include <flint/fmpq.h>
#include <flint/fmpz_vec.h>
#include <math.h>

int main()
{

    
    //inputs for delta = base ^ power
    unsigned long int base = 2;
    unsigned long int power = 30;

    //inputs for the C_N calc
    double a_0mod4 = 1 / 4;
    double b_1mod4 = (5 / 4) - (log(3) / 2);

    //calculating related inputs
    unsigned long int abs_delta = n_pow(base, power);
    double B = sqrt(abs_delta) / sqrt(3);


    //calculating largest g and largest sum
    double largest_g;

    //sets the struct of factors
    fmpq_t current_sum, current_factor_inverse, largest_sum;
    fmpq_init(largest_sum);


    for(unsigned long int g = 1; B > g; g++)
    {
        fmpq_init(current_sum);

        //this loop calculates the sum of 1/j where j are all the divisors of g
        for(unsigned long int j = 1; g >= j; j++)
        {
            //if j % g == 0 the j is a divisor of g 
            if(g % j == 0)
            {
                //sets current_factor_inverse to the inverse of j
                fmpq_init(current_factor_inverse);
                fmpq_set_ui(current_factor_inverse, 1, j);
                
                //sets current sum to the current sum plus the current factor inverse 
                fmpq_add(current_sum, current_sum, current_factor_inverse);
            
                //if the current sum is larger than the largest sum calculated 0 < fmpq_cmp(current_sum, largest_sum) will be true
                if(0 < fmpq_cmp(current_sum, largest_sum) )
                {
                    fmpq_set(largest_sum, current_sum);
                    largest_g = g;
                }
            }

        }
    }


    //sets the fraction to its lowest terms
    fmpq_canonicalise(largest_sum);


    //prints out the answer
    printf("\nFor |%s| < %ld ^ %ld = %ld \n", "\u0394",base, power, abs_delta);
    printf("Largest g: %.0lf \n", largest_g);
    printf("Largest sum is ");
    fmpq_print(largest_sum);
    printf("\n \n");

    return 0;
}