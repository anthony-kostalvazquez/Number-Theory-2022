from cmath import sqrt
import time
import math

#This code was written to explore the time savings between
#Brute Force Polynomial Multiplication
#Kronecker Substitution

#This function takes polynomials f(x), g(x) and brute force multiplys them
#INPUT: Polynomials f(x),g(x) in dictionary form fx_dic = [order of x : coefficient]``
#OUTPUT: List [t,hx_dictionary] where:
#        t = time elapsed
#        hx_dictionary is the polynomial h(x) = f(x)*g(x) in dictionary form hx_dic = [order of x : coefficient]
def Brute_force(fx_dic,gx_dic):
    start = time.time()
    #This will be populated with [order of x : coefficient]
    hx_dictionary = {}

    for i in range(len(fx_dic.keys())):
        coefficient_fx = fx_dic.get(i)
        for j in range(len(gx_dic.keys())):
            coefficient_gx = gx_dic.get(j)
            order_hx = i+j
            coefficient_hx = (coefficient_fx*coefficient_gx) + hx_dictionary.pop(order_hx, int(0))
            hx_dictionary.update({order_hx : coefficient_hx})

    end = time.time()
    t = end - start
    return [t,hx_dictionary]

#This function takes polynomials f(x), g(x) and uses kronecker substitution to multiply them
#INPUT: Polynomials f(x),g(x)
#OUTPUT: polunomial h(x) = f(x)*g(x)
#                   t = time elapsed
def kronecker_sub(fx_dic,gx_dic,bit_size):
    start = time.time()
    fx_expanded = 0
    gx_expanded = 0
    x = 10 ** bit_size
    hx_dic = {}

    #calc f(x)
    loop_count = 0
    for i in fx_dic.values():
        fx_expanded = fx_expanded + (i * (x**(loop_count)))
        loop_count = loop_count + 1
    
    #calc g(x)
    loop_count = 0
    for j in gx_dic.values():
        gx_expanded = gx_expanded + (j * (x**(loop_count)))
        loop_count = loop_count + 1

    #calc h(x)
    hx_expanded = str(fx_expanded * gx_expanded)

    #formant hx_expanded
    while len(hx_expanded) % bit_size != 0:
        hx_expanded = str(0) + hx_expanded

    #construct hx_dic
    inner_loop_count = 0
    hx_coefficient = str()
    for k in hx_expanded:
        hx_coefficient = hx_coefficient + str(k)
        if len(hx_coefficient) == bit_size: 
            inner_loop_count = inner_loop_count + 1
            hx_dic.update({(len(str(hx_expanded)) // bit_size) - inner_loop_count : int(hx_coefficient)})
            hx_coefficient = str()

    end = time.time()
    t = end - start
    return [t,hx_dic]


#Gets input from the users, prints out runtime and calcs difference between the methods
def main():
    #Prints statement to let the user know what the program does
    print("")
    print("--------------------------BEGIN--------------------------")
    print("Hello, this program will multiply polynomials f(x) by g(x)")

    #gets user input
    fx = str(input("Enter f(x) = a + bx + cx^2 ... + _x^n = abc..... (no spaces): "))
    gx = str(input("Enter g(x) = a + bx + cx^2 ... + _x^n = abc..... (no spaces): "))
    largest_co_f_g = int(input("Enter the largest co-efficient of f(x) and g(x): "))
    while (len(fx)%largest_co_f_g != 0) and (len(fx)%largest_co_f_g != 0):
        print("~~~~ERROR~~~~")
        print("Entry Not Valid Try Again")
        fx = str(input("Enter f(x) = a + bx + cx^2 ... + _x^n = abc..... (no spaces): "))
        gx = str(input("Enter g(x) = a + bx + cx^2 ... + _x^n = abc..... (no spaces): "))
        largest_co_f_g = int(input("Enter the largest co-efficient of f(x) and g(x): "))

    #initialize dictionaries (hash tables)
    fx_dic = {}
    gx_dic = {}

    #turns lists into a library with entry's [order of x : coefficient] 
    for i in range(len(fx) // largest_co_f_g):
        fx_dic.update({int(i) : int(fx[ i*largest_co_f_g : largest_co_f_g + (largest_co_f_g*i)])})
 
    for j in range(len(gx) // largest_co_f_g):
        gx_dic.update({int(j) : int(gx[ j*largest_co_f_g : largest_co_f_g + (largest_co_f_g*j)])})

    #runs the brute force method
    t_hxdic_brute_list = Brute_force(fx_dic,gx_dic)
    brute_force_hx_dic = t_hxdic_brute_list.pop(1)
    brute_force_time = t_hxdic_brute_list.pop(0)

    #finds bitsize of h(x) note: this is done apriori in the real program
    bit_size = int(len(str(max(brute_force_hx_dic.values()))))

    #runs the kronecker substitution method
    t_hxdic_kornsub_list = kronecker_sub(fx_dic,gx_dic,bit_size)
    kronsub_hx_dic = t_hxdic_kornsub_list.pop(1)
    kronsub_time = t_hxdic_kornsub_list.pop(0)

    #------------------------------------------------------------------#
    if kronsub_hx_dic == brute_force_hx_dic:
        print("--------------------------INPUT--------------------------")
        #Printing h(x)
        print("f(x) = ",end="")
        for k in range(len(fx_dic.keys())):
            if k == len(fx_dic.keys())-1:
                print(str(fx_dic.get(k)) + "x^" + str(k),end="")
            else:
                print(str(fx_dic.get(k)) + "x^" + str(k),end=" + ")
            

        #Printing h(x)
        print("")
        print("g(x) = ",end="")
        for l in range(len(gx_dic.keys())):
            if l == len(gx_dic.keys())-1:
                print(str(gx_dic.get(l)) + "x^" + str(l),end="")
            else:
                print(str(gx_dic.get(l)) + "x^" + str(l),end=" + ")
        print("")
        print("--------------------------OUTPUT--------------------------")
        
        #Printing h(x)
        print("f(x) x g(x) = ",end="")
        for m in range(len(brute_force_hx_dic.keys())):
            if m == len(brute_force_hx_dic.keys())-1:
                print(str(brute_force_hx_dic.get(m)) + "x^" + str(m),end="")
            else:
                print(str(brute_force_hx_dic.get(m)) + "x^" + str(m),end=" + ")
        
        #Printing times
        print("")
        print("The brute force algorithm took " + str(brute_force_time) + " seconds")
        print("The Kronecker substitution algorithm took " + str(kronsub_time) + " seconds")
        #print("The sophisticated Kronecker substitution algorithm took " + str() + " seconds")
        #------------------------------------------------------------------#      
main()