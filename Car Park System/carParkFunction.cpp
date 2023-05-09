#include "parking.h"
/*
	carParkFunction.cpp
	Author: M00741392
	Created: 03/04/2022
	Updated: 15/04/2022
*/
#include <iostream>
#include <string>
Vehicle::Vehicle(std::string date, std::string vehicle_number, 
 std::string time_in, std::string time_out, std::string price){
  this->date = date;
  this->vehicle_number = vehicle_number;
  this->time_in = time_in;
  this->time_out = time_out;
  this->price = price;
}


Vehicle::~Vehicle(){
}
// To access the private variable date from the class vehicle
std::string Vehicle::accessDate(){
    return date;
}
// To access the private variable time_out from class vehicle
std::string Vehicle::accessTimeOut(){
    return time_out;
}
/*This function will display the history of the vehicles as they enter 
and leave the car park.*/
std::string Vehicle::addHistory(){
   return "Date : " + date + "\nVRN : " + vehicle_number + "\nTIME_IN : " +
   time_in + "\nTIME_OUT : " + time_out + "\nParking Charge : " + price + "\n";
}
/* This function will display all vehicles with their vehicle number,
 entry and exit times, and parking costs for a specific date.*/
std::string Vehicle::specificDate(){
   return "VRN : " + vehicle_number + "\nTIME_IN : " + time_in + "\nTIME_OUT : "
   + time_out + "\nParking Charge : " + price ;
}

