/*
	parking.h
	Author: M00741392
	Created: 01/03/2022
	Updated: 15/04/2022
*/
#include "parking.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

/*Function to calculate the price of the vehicle when it left the car park*/

std::string calculatePrice(int hour, int minute, int second){
    if(hour == 0 && minute >= 30){
        // If it takes 30 to 59 minutes to leave
        return "£1.50";
    }else if(hour == 1){
        // If it takes 1 to 1 hour 59 minutes to leave
        return "£3.00";
    }else if(hour == 2 || hour == 3){
        // If it takes 2 to 3 hour 59 minutes to leave
        return "£5.00";
    }else if(hour == 4 || hour == 5 || hour == 6 || hour == 7){
        // If it takes 4 to 7 hour 59 minutes to leave
        return "£15.00";
    }else if(hour >= 8){
        // If it takes 8 hours or more to leave
        return "£30.00";
    }else{
        // Else if it takes less than 30 minutes to leave 
        return "FREE";
    }
}

/*Void function to calculate the difference between the time the vehicle 
entered and left the car park*/
void timeDifference(struct Time time_in, struct Time time_out, 
struct Time *diff){
    /* This will allow to find the difference between, for example,
     entry times of 12:30:30 and exit times of 12:31:20. */
    if(time_in.sec > time_out.sec){
        time_out.min = time_out.min - 1;
        time_out.sec = time_out.sec + 60; 
    }
    // The difference for second
    diff->sec = abs(time_out.sec - time_in.sec);
    /* This will allow to find the difference between, for example, 
    entry times of 12:30:00 and exit times of 13:20:00. */
    if(time_in.min > time_out.min){
        time_out.hr = time_out.hr - 1;
        time_out.min = time_out.min + 60;
    } 
    // The difference for minute
    diff->min = abs(time_out.min-time_in.min);
    
    /* This will allow to find the difference between, for example, 
    the entry time of 23:00:00 and the exit time of 3:00:00.*/ 
    if(time_in.hr > time_out.hr){
        time_out.hr = time_out.hr + 24;    
    }
    // The difference for hour
    diff->hr = abs(time_out.hr-time_in.hr);
}
/*This function will make sure that the user enters a valid time.*/
void timeValidation(struct Time *timeV, std::string hour, std::string minute, 
std::string second){
/* This while loop will make sure that the user enters a number.*/   
    while(hour.find_first_not_of("0123456789") 
    !=  std::string::npos || 
    minute.find_first_not_of("0123456789") 
    !=  std::string::npos ||
    second.find_first_not_of("0123456789") 
    !=  std::string::npos){
        std::cout << "Please Enter a number: " << std::endl;
        std::cin >> hour >> minute >> second;
    }
    /*convert string to integer*/
    timeV->hr = stoi(hour);
    timeV->min = stoi(minute);
    timeV->sec = stoi(second);
/* This while loop will make sure that the user enters a valid hour, minute,
 and second.*/               
    while(timeV->hr < 0 || timeV->hr >= 24 ||
          timeV->min < 0 || timeV->min >=60 ||
          timeV->sec < 0 || timeV->sec >=60){
              
        std::cout << "Please Enter a valid time:" << std::endl;
        std::cin >> hour >> minute >> second;
        while(hour.find_first_not_of("0123456789") 
        !=  std::string::npos || 
        minute.find_first_not_of("0123456789") 
        !=  std::string::npos ||
        second.find_first_not_of("0123456789") 
        !=  std::string::npos){
            std::cout << "Please Enter a number: " << std::endl;
            std::cin >> hour >> minute >> second;
        }                
        timeV->hr = stoi(hour);
        timeV->min = stoi(minute);
        timeV->sec = stoi(second);
    }            
}
/*This function will make sure that the user enters a valid date.*/
void dateValidation(struct Date *date, std::string day, std::string month, 
std::string year){
/* This while loop will make sure that the user enters a number.*/   
    while(day.find_first_not_of("0123456789") 
    !=  std::string::npos || 
    month.find_first_not_of("0123456789") 
    !=  std::string::npos ||
    year.find_first_not_of("0123456789") 
    !=  std::string::npos){
        std::cout << "Please Enter a number: " << std::endl;
        std::cin >> day >> month >> year;
    }
    /*convert string to integer*/
    date->dy = stoi(day);
    date->mth = stoi(month);
    date->yr = stoi(year);
    while(date->dy <= 0 || date->dy > 31 ||
          date->mth <= 0 || date->mth >12 ||
          date->yr < 2022 ){
              
        std::cout << "Please Enter a valid date:" << std::endl;
        std::cin >> day >> month >> year; 
        while(day.find_first_not_of("0123456789") 
        !=  std::string::npos || 
        month.find_first_not_of("0123456789") 
        !=  std::string::npos ||
        year.find_first_not_of("0123456789") 
        !=  std::string::npos){
            std::cout << "Please Enter a number: " << std::endl;
            std::cin >> day >> month >> year;
        }
        date->dy = stoi(day);
        date->mth = stoi(month);
        date->yr = stoi(year);
    }
}


int main(){
    //variable to choose different options from the menu.
    std::string menu_number = "-1";
    std::string vehicle_number;
    std::string dateV;
    std::string timeIn;
    std::string timeOut;
    std::string price;
    struct Time time_in, time_out, diff;
    struct Date date;
    /* This variable is used when the user enters a vehicle number to make
     the vehicle leave the car park.*/
    std::string vehicleNumberExit;
    /* This 2D array will store the data of the vehicle when it enters
     the car park. */
    std::string vehicleEnterDetails[200][3];
    /* The vector historyDetails will store the history of the vehicle
     as it entered and left the car park.*/
    std::vector<Vehicle*> historyDetails;

    /*This 2D array will store the entry time by hour, minute, and second. */
    int arrTimeIn[200][3];
    int sizeHistory = 0;
    /*This variable is used when the user enters a date to display all vehicles
     that enter or leave the car park on that date.*/
    std::string dateVehicle;
    std::ofstream writeHistory("history.txt");

    // Menu of the car park
    while (menu_number != "0"){
        std::string sameNumValid = "-1";
        
        std::cout << "-------------------Car Park System-------------------\n" 
        << std::endl;
        std::cout << "Enter a number to perform a task:" << std::endl;
        std::cout << "1 - Add a vehicle to the parking." << std::endl;
        std::cout << "2 - Remove a vehicle to the parking." << std::endl;
        std::cout << "3 - Show the vehicles which are in the parking." 
        << std::endl; 
        std::cout << "4 - Show the history." << std::endl;
        std::cout << "5 - Show vehicles with its entry time, exit time and \n"
        << "    parking charge for a specific date." << std::endl;
        std::cout << "0 - Exit." << std::endl;
    
        std::cout << "Choose an option:" << std::endl;
        std::cin >> menu_number;
        /* If the user does not enter 1, 2, 3, 4, 5, or 0, this while loop will
         keep asking to enter a valid number.*/
        while (menu_number != "1" && menu_number != "2" && menu_number != "3" 
        && menu_number != "4" && menu_number != "5" && menu_number != "0"){
          std::cout << "Please Enter a valid number:" << std::endl;
          std::cin >> menu_number;
        } 
        int notExist = 0;
        // If the user chooses option 1.
        if(menu_number == "1"){
            std::string sDateDay;
            std::string sDateMonth; 
            std::string sDateYear;
            std::cout << "Enter the date. Enter the day, month and year " << 
            "respectively:" << std::endl;
            std::cin >> sDateDay >> sDateMonth >> sDateYear;
            
            dateValidation(&date, sDateDay, sDateMonth, sDateYear);
            
            std::cout << "Enter the vehicle number:" << std::endl;
            std::cin >> vehicle_number;

/*This while loop will make sure that the user enters a 
different vehicle number.*/
            while(sameNumValid != "0"){
                for(int m = 0; m < 200; m++){
/* Check if the vehicle number entered by the user is in the 2D array
 vehicleEnterDetails*/
                    if(vehicleEnterDetails[m][1] == vehicle_number){
                        std::cout << "This vehicle number is already used. " 
                        <<"Please Enter a different vehicle number:" 
                        << std::endl;
                        std::cin >> vehicle_number;
                        m = 200; // get out of the for loop
                        notExist = 0; // reset the variable to 0
                    }else{
                       notExist = notExist + 1; 
                    }
                }
                if(notExist == 200){
                    sameNumValid = "0";
                }
            }
            std::string sTimeInHr;
            std::string sTimeInMin; 
            std::string sTimeInSec;
            std::cout << "Enter the time the vehicle entered the car park. " <<
            "Enter hours, minutes and seconds respectively: " << std::endl;
            std::cin >> sTimeInHr >> sTimeInMin >> sTimeInSec;
            
            timeValidation(&time_in, sTimeInHr, sTimeInMin, sTimeInSec);
            
            /* Store the date, vehicle number, and time_in in the 2D array
             vehicleEnterDetails*/
            for(int n = 0; n < 200; n++){
    /*Check if a parking is empty to add the vehicle*/
                if(vehicleEnterDetails[n][0] == ""){
                    vehicleEnterDetails[n][0] = 
                    std::to_string(date.dy) + "/" + 
                    std::to_string(date.mth) + "/" +
                    std::to_string(date.yr); 
                    vehicleEnterDetails[n][1] = vehicle_number;
                    vehicleEnterDetails[n][2] = 
                    std::to_string(time_in.hr) + ":" + 
                    std::to_string(time_in.min) + ":" +
                    std::to_string(time_in.sec); 
            // Store the hour, minute, and second in the 2D array arrTimeIn.
                    arrTimeIn[n][0] = time_in.hr;
                    arrTimeIn[n][1] = time_in.min;
                    arrTimeIn[n][2] = time_in.sec;
                    n = 200;
                }
            }
            //Variable for the class Vehcile
            dateV = std::to_string(date.dy) + "/" + std::to_string(date.mth) + 
            "/" + std::to_string(date.yr);
            timeIn = std::to_string(time_in.hr) + ":" + 
            std::to_string(time_in.min) + ":" + std::to_string(time_in.sec);
            timeOut = "";
            price = "";

            /*The variable sizeHistory will determine the size of the vector
             historyDetails*/
            sizeHistory = sizeHistory + 1;
            /*Store all the data of the vehicle in the vector.*/
            historyDetails.push_back(new Vehicle(dateV, vehicle_number, timeIn,
            timeOut, price));
            
            std::cout << "\nA vehicle has entered the parking <---\n" 
            << std::endl;

        }
        int error = 0;
        // If the user chooses option 2
        if(menu_number == "2"){
            std::cout << "Enter the vehicle number that is leaving.: "
            << std::endl;
            std::cin >> vehicleNumberExit;


/* This for loop will delete the vehicle that has left the car park from the 2D
 array vehicleEnterDetails. It will also insert data into the vector
  historyDetails.*/
            for(int c = 0; c < 200; c++){
/* Check if the vehicleNumber entered by the user exists in the 2D array
vehicleEnterDetails*/
                if(vehicleNumberExit != vehicleEnterDetails[c][1]){
                        error = error + 1;
                }else{
                    std::string sTimeOutHr;
                    std::string sTimeOutMin; 
                    std::string sTimeOutSec;
                    std::cout << "Enter the time the vehicle exited the " << 
                    "car park. Enter hours, minutes and seconds " << 
                    "respectively: " << std::endl;
                    std::cin >> sTimeOutHr >> sTimeOutMin >> sTimeOutSec;
                    
                    timeValidation(&time_out, sTimeOutHr, sTimeOutMin, 
                    sTimeOutSec);
                    
                    timeOut = std::to_string(time_out.hr) + 
                    ":" + std::to_string(time_out.min) + ":" + 
                    std::to_string(time_out.sec);
                    
                    time_in.hr = arrTimeIn[c][0];
                    time_in.min = arrTimeIn[c][1];
                    time_in.sec = arrTimeIn[c][2];
    /* Call the function timeDifference to return the difference between 
    entry time and exit time.*/
                    timeDifference(time_in, time_out, &diff);
    /*Assign the function calculatePrice that returns the price of the 
    vehicle to the variable price.*/
                    price = 
                    calculatePrice(diff.hr, diff.min, diff.sec);
                    /*Store all the data of the vehicle in the vector.*/
                    historyDetails.push_back(new Vehicle(
                    vehicleEnterDetails[c][0], vehicleEnterDetails[c][1],
                    vehicleEnterDetails[c][2], timeOut, price));
                    // Delete the data of the vehicle from the 2d array 
                    vehicleEnterDetails[c][0] = "";
                    vehicleEnterDetails[c][1] = "";
                    vehicleEnterDetails[c][2] = "";
                    
                    sizeHistory = sizeHistory + 1;
                    std::cout << "\nA vehicle has left the parking --->\n" 
                    << std::endl;
                    
                    c = 200;
                }                
            }
                /* If there is no vehicle with the vehicle number the user
                 has entered, it will return the user to the menu with an 
                 error message.*/
            if(error == 200){
                std::cout << "Error. This vehicle number does not exist."
                << std::endl;
            }

        }
        /* This option will display all the vehicles which are currently in the
        car park*/
        if(menu_number == "3"){
            int empty = 0;
            std::cout << std::endl;
            for(int i = 0; i < 200; i++){
                if(vehicleEnterDetails[i][0] != ""){
                    std::cout << "-----Parking " << i+1 << "-----" << std::endl;
                    for(int j = 0; j < 3; j++){
                        if(j == 0){
                            std::cout << "Date : " << vehicleEnterDetails[i][j] 
                            << std::endl;
                        }
                        if(j == 1){
                            std::cout << "VRN : " << vehicleEnterDetails[i][j] 
                            << std::endl;
                        }
                        if(j == 2){
                            std::cout << "Time_IN : " << 
                            vehicleEnterDetails[i][j] << std::endl;
                        }
                    }    
                }else{
                    empty = empty + 1;
                }
            }
            if(empty == 200){
                std::cout << "The car park is currently empty."<<std::endl;
            }
            std::cout << std::endl;
        }
        /*This option will display the history of when a vehicle has entered
         and left the car park.*/
        if(menu_number == "4"){
            std::cout << std::endl;
            for(int g = 0; g < sizeHistory; g++){
                if(historyDetails[g]->accessTimeOut() == ""){
                    std::cout << "----Entered the car park----"
                    << std::endl;    
                }else{
                    std::cout << "-----Left the car park------"
                    << std::endl;                      
                }
                std::cout << historyDetails[g]->addHistory();
            }
            std::cout << std::endl;
        }
        /*This option will allow the user to view all the vehicles that have
         entered and left the car park on a specific date.*/
        int error_date = 0;
        if(menu_number == "5"){
            std::string dateDay;
            std::string dateMonth;
            std::string dateYear;
            
            std::cout << "Enter a date. Enter the day, month, year " << 
            "respectively:" << std::endl;
            std::cin >> dateDay >> dateMonth >> dateYear; 
            std::cout << std::endl;
            
            dateValidation(&date, dateDay, dateMonth, dateYear);
            
            dateVehicle = std::to_string(date.dy) + "/" + 
            std::to_string(date.mth) + "/" + std::to_string(date.yr); 
            
/*This for loop will display the date that the user has entered. It will make
 sure that the user entered a date where a vehicle has entered or left the
  car park.*/
            for(int p = 0; p < sizeHistory; p++){
                if(dateVehicle == historyDetails[p]->accessDate() &&
                    historyDetails[p]->accessTimeOut() != ""){
                    std::cout << "/---------" << dateVehicle << "---------\\ \n" 
                    << std::endl;  
                    // Get out of the loop
                    p = sizeHistory;
                }   
            }
/* This loop will display the history of when the vehicles left the car park. 
The date of the vehicle that left the car park has to be equal to the date
 typed by the user in order to be displayed.*/
            std::cout << "----------------------------" << std::endl;
            for(int u = 0; u < sizeHistory; u++){
                if(dateVehicle != historyDetails[u]->accessDate() ||
                    historyDetails[u]->accessTimeOut() == ""){
                    error_date = error_date + 1; 
                }else{

                    std::cout << historyDetails[u]->specificDate() <<
                    std::endl;
                    std::cout << "----------------------------" 
                    << std::endl;

                }      
            }
            /* This if statement is when the user entered a date where the
             vehicle has not left the car park yet.*/
            if (error_date == sizeHistory){
                std::cout << "Error. There is no vehicle that has left the"
			<< " car park on this date." << std::endl;
            }
            
        }
        
    }
    /*This for loop will add the data from the vector historyDetails to the
     file history.txt.*/
    for(int w = 0; w < sizeHistory; w++){
        if(historyDetails[w]->accessTimeOut() == ""){
            writeHistory << "----Entered the car park----"
            << "\n";    
        }else{
            writeHistory << "-----Left the car park------"
            << "\n";                      
        }
       writeHistory << historyDetails[w]->addHistory() << "\n";
    }
    
    writeHistory.close();
    

    for (Vehicle* ve : historyDetails){
      delete ve;
    }
    historyDetails.clear();
    
}
