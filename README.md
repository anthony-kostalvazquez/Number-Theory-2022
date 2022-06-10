# Number-Theory-2022
Here is a repository of all my number theory codes I built during my research term summer 2022

--poly_mult.py--
Python code that multiplys polynomials using kroneker substitutuion and a brute force method and times the results

--Discrete_Log_Solver.py--
python code that solves the descrete logrythm problem using a brute force approach and the famous babystep giantstep algortythm

|-------------------------------sample output-------------------------------|
|                                                                           |
|   Brute Force Algorithm time:  320.0532867908478 Seconds                  |
|   And Got the Solution 175 ^ 72626 = 63368 (mod 77711 )                   |
|                                                                           |
|   Baby-Step Giant-Step Algorithm time:  0.0010008811950683594 Seconds     |
|   And Got the Solution 175 ^ 72626 = 63368 (mod 77711 )                   |
|                                                                           |
|-------------------------------sample output-------------------------------|


--Discrete_Log_Solver.c--
this is a folder that contains a main function and a library in c to solve the descrete logrythm problem a brute force approach and the famous babystep giantstep algortythm.
it also uses the flint library found at https://www.flintlib.org/ 
it uses the same algorythms as in my other program Discrete_Log_Solver.py however its much faster

|-------------------------------sample output-------------------------------|
|                                                                           |
|   Brute Force Algorithm time: 0.008575   Seconds                          |
|   And Got the Solution 175 ^ 72626 = 63368 (mod 77711)                    |
|                                                                           |
|   Baby-Step Giant-Step Algorithm time:  0.000150 Seconds                  |
|   And Got the Solution 175 ^ 72626 = 63368 (mod 77711)                    |
|                                                                           |
|-------------------------------sample output-------------------------------|
