#This is a code that times the famous baby-step giant-step algorithm 
#versus brute force written in python

#The goal of these algs is to find an integer x such that a^x = b (mod n)
#a is a generator of the group
#b is an element mod n (0,1,....,n-1)

###################FUN###################
#              Try To Imput             #     
#             n = 77711                 #
#             a = 175                   #
#             b = 63368                 #
###################FUN###################

import math
import time

#Takes integers n,a,b and solves for x in the equation a^x = b (mod n)
#Using the famous baby-step giant-step algorithm and times it
def babystepgiantstep(n,a,b):  
    start = time.time()
    x = str("no solution")
    #proof.
    #Now let x=im+j where
    #m = ceil(sqrt(n))
    #0 <= i < m
    #0 <= j < m
    #            Then
    #          a^x = b (mod n)
    #=>   a^(im+j) = b (mod n)
    #=> a^(im)*a^j = b (mod n)
    #=> 1*a^j = (a^(-m))^i * b (mod n)
    #Thus we only have to find a i and j such that it satifies the above

    m = math.ceil(math.sqrt(n-1))
    
    hash_table={} #This will store all pairs (j,a^j)
    
    #Giant Steps
    for i in range(0,m-1):
        hash_table[b*pow(a,-(i*m),n)%n] = int(i)

    #Baby Steps
    for j in range(0,n):
        y = (a**j)%n
        if y in hash_table.keys():
            x = hash_table.get(y)*m + j
            break

    end = time.time()
    print("Baby-Step Giant-Step Algorithm time: ",end - start, "Seconds")
    print("And Got the Solution",a, "^", x ,"=", b, "(mod",n,")" )
    print("")

#Takes integers n,a,b and solves for x in the equation a^x = b (mod n)
#Using a brute force method
def bruteforce(n,a,b):
    x = str("no solution")
    start = time.time()
    for i in range(0,n-1):
        if int((a**i)%n) == int(b):
            x = i
            break
    end = time.time()
    print("")
    print("Brute Force Algorithm time: ",end - start, "Seconds")
    print("And Got the Solution",a, "^", x ,"=", b, "(mod",n,")" )
    print("")

#Will take input n and output the boolian 
#true if its prime and false if its composite
def primality_test_brute(n):
    prime_bool = True
    for i in range(2,n-1):
        if n%i == 0:
            prime_bool = False
            print("Not Prime!!!!")
            break
    return prime_bool

def main():
    print("Welcome, lets solve the problem a^x = b (mod n)")
    
    n=int(4) #initialize 
    
    #Getting Inputs
    while primality_test_brute(int(n)) == False:
        n = int(input("Enter a prime n: "))
    a = int(input("Enter an integer a: ")) #to get a solution a has to be a primitive root of n
    b = int(input("Enter an integer b: "))
    
    #Formating Inputs
    a = a%n
    b = b%n

    #Solving a^x = b (mod n)
    bruteforce(int(n),int(a),int(b))
    babystepgiantstep(int(n),int(a),int(b))

main()