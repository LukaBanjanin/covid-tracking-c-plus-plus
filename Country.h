// Created by Luka Banjanin
// lbanjani@uwo.ca
// 250968309

//include guard
#ifndef COUNTRY_H
#define COUNTRY_H

#include <vector>
#include <string>
#include <iostream>
#include <string>
using namespace std;

class Country {
public:  ~Country();//destructor
    //constructor
    Country(string, string, int, int, int, int, int, int);

    //cetter functions
    string get_country_name();
    string get_country_code();
    int get_new_confirmed_cases();
    int get_new_deaths();
    int get_new_recovered_cases();
    int get_total_confirmed_cases();
    int get_total_deaths();
    int get_total_recovered_cases();

private:
    //private variables
    string name;
    string code;
    int ncc;
    int nd;
    int nrc;
    int tcc;
    int td;
    int trc;

};

#endif //COUNTRY_H