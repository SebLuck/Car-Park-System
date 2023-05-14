# Car-Park-System-C++
This program is on a parking management system that is written in C++. The user can add, remove, and view the vehicles in the car park. The maximum number of vehicles that can enter the car park is 200.


The system can track vehicles entering and exiting a car park, calculate parking charges if required, store the details in a file, and allow functionality to produce a report for a given date with a list of number plates, enter/exit times, and parking price.  
The data structures used are a two-dimensional array and a vector.  

# Limitation
One of the limitations of the program is that it does not have a good validation for the input of vehicle numbers. For example, if you enter a vehicle number like "abcd" or "1234" as input, the program will accept it and store it in the array and vector. It will be better if there is a format for the vehicle number. 

# Getting Started
- To run the program, you will need to type this command first in your terminal: ` g++ carParkFunction.cpp mainCarPark.cpp -o output`
- Then type the command `./output`
