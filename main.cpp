// Created by Luka Banjanin
// lbanjani@uwo.ca
// 250968309

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>  
#include <algorithm>   
#include "Country.h"

using namespace std;

int main() {

    fstream file;
    file.open("summary.csv", ios::in);//open the csv file we will be working with
    if (!file.is_open()) { cout << "Could not open file... Aborting the program..." << endl;//check that the file was opened properly
    return 0; }

    std::vector<Country> container;//vector we will use to store all of our country objects
    //all variables relevant for reading in data from csv file
    string country_name;
    string country_code;
    string country_date;
    string country_new_confirmed_cases;
    string country_new_deaths;
    string country_new_recovered_cases;
    string useless_1;
    string useless_2;
    string country_total_confirmed_cases;
    string country_total_deaths;
    string country_total_recovered_cases;
    string headers;

    int ordering;//user's choice for either ascending or descending
    int metric;//user's choice for the metric they are interested in
    int symbol_worth;//to be used when printing out the graphs

//The following 6 structs will be used in combination with the std::sort call to sort the vector according to whichever 1 of the 6 metrics the user selected
    struct sorting_helper_function_1 {
        inline bool operator() (Country& tmp1, Country& tmp2)
        {
            return (tmp1.get_new_confirmed_cases() < tmp2.get_new_confirmed_cases());
        }
    };

    struct sorting_helper_function_2 {
        inline bool operator() (Country& tmp1, Country& tmp2)
        {
            return (tmp1.get_new_deaths() < tmp2.get_new_deaths());
        }
    };

    struct sorting_helper_function_3 {
        inline bool operator() (Country& tmp1, Country& tmp2)
        {
            return (tmp1.get_new_recovered_cases() < tmp2.get_new_recovered_cases());
        }
    };

    struct sorting_helper_function_4 {
        inline bool operator() (Country& tmp1, Country& tmp2)
        {
            return (tmp1.get_total_confirmed_cases() < tmp2.get_total_confirmed_cases());
        }
    };

    struct sorting_helper_function_5 {
        inline bool operator() (Country& tmp1, Country& tmp2)
        {
            return (tmp1.get_total_recovered_cases() < tmp2.get_total_recovered_cases());
        }
    };

    struct sorting_helper_function_6 {
        inline bool operator() (Country& tmp1, Country& tmp2)
        {
            return (tmp1.get_total_deaths() < tmp2.get_total_deaths());
        }
    };

    //grab the first row containing the headers in the file
    getline(file, headers, '\n');

    while (file.good()) {//while loop that runs until the entire file has been read in
 
        getline(file, country_name, ',');

        //manually check for all special cases and manually alter the names
        if (country_name == "\"Macedonia") {
            country_name = "\"Macedonia\"";
            getline(file, country_name, ',');
        } else if (country_name == "\"Tanzania") {
            country_name = "\"Tanzania\"";
            getline(file, country_name, ',');
        } else if (country_name == "\"Iran") {
            country_name = "\"Iran\"";
            getline(file, country_name, ',');
        } else if (country_name == "\"Taiwan") {
            country_name = "\"Taiwan\"";
            getline(file, country_name, ',');
        }

            //read in the rest of the data for 1 country (1 row in the csv file) and store it in these temporary variables
            getline(file, country_code, ',');
            getline(file, country_date, ',');
            getline(file, country_new_confirmed_cases, ',');
            getline(file, country_new_deaths, ',');
            getline(file, country_new_recovered_cases, ',');
            getline(file, useless_1, ',');
            getline(file, useless_2, ',');
            getline(file, country_total_confirmed_cases, ',');
            getline(file, country_total_deaths, ',');
            getline(file, country_total_recovered_cases, '\n');

            //initialize a country object with the row of data we just read in and push it into our vector
            container.push_back(Country(country_name, country_code, stoi(country_new_confirmed_cases), stoi(country_new_deaths), stoi(country_new_recovered_cases), stoi(country_total_confirmed_cases), stoi(country_total_deaths),
                                  stoi(country_total_recovered_cases)));
                            
    }

do {//read metric from user
        cout << endl << " Type the number corresponding to the metric you are interested in, then hit ENTER\n\n New Confirmed Cases: 1 \n New Deaths: 2 \n New Recovered Cases: 3 \n Total Confirmed Cases: 4 \n Total Recovered Cases: 5 \n Total Deaths: 6 \n\n";
        cin >> metric;
} while (metric != 1 && metric != 2 && metric != 3 && metric != 4 && metric != 5 && metric != 6 && metric != 1);//error handling
        
do {//read desired ordering from user 
        cout << "\n Type the number corresponding to the order in which you want the data to be displayed, then hit ENTER\n\n Descending order: 1 \n Ascending order: 2 \n\n";
        cin >> ordering;
        cout << endl;
} while (ordering != 1 && ordering != 2);//error handling
        

//the following comment will be lengthy but it will aim to exlain the rest of the code because it does get fairly repetitive
//the outer if statement has 2 parts, the first one being the descending option for graph viewing and the second one being the ascending option
//the difference between the 2 outer loops is that in the ordering = 1, we are looking at the top 10 country objects in the sorted vector while in ordering = 2 we are looking at the bottom 10 country objects in the sorted vector 
//the difference in the inner if statements (1-6 depending on what the user is interested in seeing) is simply the sorting helper struct they use specific to each case, and which variabes they request to access when sorting the objects which is once again, specific to each case
if(ordering == 1){

    if(metric == 1){
        std::sort (container.begin(), container.end(), sorting_helper_function_1());//sort the vector for the case we want using it's particular sorting helper struct
        symbol_worth = (container.at(container.size() -1).get_new_confirmed_cases()) / 70;//we want longest line to be 70 # long so find out how much each # is by looking at the relevant variable in the largest country in our vector
        
        for(int i = 1; i < 11; i++) {//for loop that will access the 10 countries we are interested in
        int bar_length;//will be used as variable in innter for loop for printing out the correct number of hashtags
        string code_tmp;//will contain country code for output to user
        bar_length = container.at(container.size() - i).get_new_confirmed_cases() / symbol_worth;//scale each countries # relative to that of the longest countries bar
        code_tmp = container.at(container.size() - i).get_country_code();//get the country code of the country we want
        cout << code_tmp << " | ";//print the couuntry code and a veetical bar
        
            for(int j = 0; j < bar_length; j++) {//inner for loop that prints the correct number of # for each country
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "New Confirmed Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;

    }
    else if (metric == 2){
        std::sort (container.begin(), container.end(), sorting_helper_function_2());
        symbol_worth = (container.at(container.size() -1).get_new_deaths()) / 70;
        
        for(int i = 1; i < 11; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(container.size() - i).get_new_deaths() / symbol_worth;
        code_tmp = container.at(container.size() - i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "New Deaths: Each # is approx. " << symbol_worth << " cases" << endl << endl;

    }
    else if (metric == 3){
        std::sort (container.begin(), container.end(), sorting_helper_function_3());
        symbol_worth = (container.at(container.size() -1).get_new_recovered_cases()) / 70;
        
        for(int i = 1; i < 11; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(container.size() - i).get_new_recovered_cases() / symbol_worth;
        code_tmp = container.at(container.size() - i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "New Recovered Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
    else if (metric == 4){
        std::sort (container.begin(), container.end(), sorting_helper_function_4());
        symbol_worth = (container.at(container.size() -1).get_total_confirmed_cases()) / 70;
        
        for(int i = 1; i < 11; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(container.size() - i).get_total_confirmed_cases() / symbol_worth;
        code_tmp = container.at(container.size() - i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Total Confirmed Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
    else if (metric == 5){
        std::sort (container.begin(), container.end(), sorting_helper_function_5());
        symbol_worth = (container.at(container.size() -1).get_total_recovered_cases()) / 70;
        
        for(int i = 1; i < 11; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(container.size() - i).get_total_recovered_cases() / symbol_worth;
        code_tmp = container.at(container.size() - i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Total Recovered Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
    else if (metric == 6){
        std::sort (container.begin(), container.end(), sorting_helper_function_6());
        symbol_worth = (container.at(container.size() -1).get_total_deaths()) / 70;
        
        for(int i = 1; i < 11; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(container.size() - i).get_total_deaths() / symbol_worth;
        code_tmp = container.at(container.size() - i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Total Deaths: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
}

if(ordering == 2){

    if(metric == 1){
        std::sort (container.begin(), container.end(), sorting_helper_function_1());
        symbol_worth = container.at(9).get_new_confirmed_cases();
        
        for(int i = 0; i < 10; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(i).get_new_confirmed_cases();
        code_tmp = container.at(i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "----------------------------------------------" << endl;
        cout << "New Confirmed Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;

    }
    else if (metric == 2){
        std::sort (container.begin(), container.end(), sorting_helper_function_2());
        symbol_worth = container.at(9).get_new_deaths();
        
        for(int i = 0; i < 10; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(i).get_new_deaths();
        code_tmp = container.at(i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "-------------------------------------" << endl;
        cout << "New Deaths: Each # is approx. " << symbol_worth << " cases" << endl << endl;

    }
    else if (metric == 3){
        std::sort (container.begin(), container.end(), sorting_helper_function_3());
        symbol_worth = container.at(9).get_new_recovered_cases();
        
        for(int i = 0; i < 10; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(i).get_new_recovered_cases();
        code_tmp = container.at(i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "----------------------------------------------" << endl;
        cout << "New Recovered Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
    else if (metric == 4){
        std::sort (container.begin(), container.end(), sorting_helper_function_4());
        symbol_worth = container.at(9).get_total_confirmed_cases();
        
        for(int i = 0; i < 10; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(i).get_total_confirmed_cases();
        code_tmp = container.at(i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Total Confirmed Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
    else if (metric == 5){
        std::sort (container.begin(), container.end(), sorting_helper_function_5());
        symbol_worth = container.at(9).get_total_recovered_cases();
        
        for(int i = 0; i < 10; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(i).get_total_recovered_cases();
        code_tmp = container.at(i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "-------------------------------------------------" << endl;
        cout << "Total Recovered Cases: Each # is approx. " << symbol_worth << " cases" << endl << endl;
        
    }
    else if (metric == 6){
        std::sort (container.begin(), container.end(), sorting_helper_function_6());
        symbol_worth = container.at(9).get_total_deaths();
        
        for(int i = 0; i < 10; i++) {
        int bar_length;
        string code_tmp;
        bar_length = container.at(i).get_total_deaths();
        code_tmp = container.at(i).get_country_code();
        cout << code_tmp << " | ";
        
            for(int j = 0; j < bar_length; j++) {
                cout << "#";
            }

            cout << endl;
        }
        cout << "---------------------------------------" << endl;
        cout << "Total Deaths: Each # is approx. " << symbol_worth << " cases" << endl << endl;   
    }
}

//end of program
return 0;
}
