#ifndef _PARKING_H_
#define _PARKING_H_
/*
	parking.h
	Author: M00741392
	Created: 31/03/2022
	Updated: 15/04/2022
*/


#include <iostream>
#include <string>

/*Class that contains all the attributes of the vehicle and operations like
 displaying the history of the car park and calling private variables like
  date and time_out*/
class Vehicle {
    private:
        std::string date;
        std::string vehicle_number;
        std::string time_in;
        std::string time_out;
        std::string price;

    public:
        Vehicle(std::string date, std::string vehicle_number, 
        std::string time_in, std::string time_out, std::string price);
        virtual ~Vehicle();
        std::string addHistory();
        std::string accessDate();
        std::string specificDate();
        std::string accessTimeOut();
};  

// A structure to store the time in second, minute and hour.
struct Time{
  int sec;
  int min;
  int hr;
};
// A structure to store the date in day, month and year.
struct Date{
    int dy;
    int mth;
    int yr;
};
#endif
