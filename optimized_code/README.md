# Code Optimization 

The goal of this project is to optimize the C++ code of the 2D histogram filter. 

## Optimization Techniques

* **Avoiding extra if statements**: Optimizing if statements to increase the efficiency of the code; this includes removing unnecessary checks and using if else construct properly. 

* **Avoiding nested for loops**: Sometimes nested for loops can be avoided, which reduces the execution time of the program.
 
* **Avoiding Extra variables**: Creating extra variables leads to more memory consumption. 

* **Reserving Space for vectors**: Memory space for the vectors whose size is known beforehand should be reserved; this saves on memory and gives a boost while creating the vector. 

* **Passing variables by reference**: Variables are passed by value by default in C++, i.e. variables are always copied when being passed to functions. Copying of variables leads to more memory consumption which should be avoided for larger variables such as vectors.  

* **Using Static Keyword**: Static keyword makes a variable like a global variable, that is it saves the memory the first time a function is called and let the function use the same memory space every other time it is called. 

* **GCC Optimizations**: GCC provides flags to optimize C++ code. More information on that [here](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html). Three levels of optimizations are available: -O1, -O2, -O3 


## Code Execution 

To run without GCC optimizations: 
```
cd /optimized_code/
g++ -std=c++11 main.cpp blur.cpp initialize_beliefs.cpp move.cpp normalize.cpp print.cpp sense.cpp zeros.cpp
./a.out 
```
To run with GCC optimizations: (Change optimization flag)
```
cd /optimized_code/
g++ -std=c++11 -O3 main.cpp blur.cpp initialize_beliefs.cpp move.cpp normalize.cpp print.cpp sense.cpp zeros.cpp
./a.out 
```


## Execution Output 

Execution time (in milliseconds) of the code is monitored by running every function for 10000 iterations. The best execution time achieved by the code is 

| File Name  | Original Problem Code execution time | Optimized  Code execution time  | Optimized  Code execution with O3 GCC flag execution time |
 ----------- | ------------------------------------ | ------------------------------- | ----------------------------------------------------------- 
Initialize Beliefs | 43.42 | 13.518 | 1.802 |
Sense | 56.057 | 14.967 | 3.444 | 
Blur | 151.49 | 67.38 | 7.748 |
Normalize | 56.39 | 13.157 | 1.573 |
Move | 51.566 | 16.536 | 2.31 |
**Total** | **358.923** | **125.558** | **16.877** |


## Applications 

Code optimizations reduce the execution time of a program while also reducing the memory footprint, making it feasible to run the code on an embedded device or in real-time scenarios. 

## Acknowledgement 

[Udacity Computer Vision Nanodegree](https://github.com/udacity/) 

## Author 
[Abhishek Tandon](https://github.com/Tandon-A)
