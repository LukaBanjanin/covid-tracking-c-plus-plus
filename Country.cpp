// Created by Luka Banjanin
// lbanjani@uwo.ca
// 250968309

#include "Country.h"
#include <utility>

//constructor
Country::Country(string country_name, string country_code, int country_new_confirmed_cases, int country_new_deaths, int country_new_recovered_cases, int country_total_confirmed_cases, int country_total_deaths, int country_total_recovered_cases) {
    name = country_name;
    code = country_code;
    ncc = country_new_confirmed_cases;
    nd = country_new_deaths;
    nrc = country_new_recovered_cases;
    tcc = country_total_confirmed_cases;
    td = country_total_deaths;
    trc = country_total_recovered_cases;
}
//getter functions for all private variables
string Country::get_country_name() {
    return name;
}
string Country::get_country_code() {
    return code;
}
int Country::get_new_confirmed_cases() {
    return ncc;
}
int Country::get_new_deaths() {
    return nd;
}
int Country::get_new_recovered_cases() {
    return nrc;
}
int Country::get_total_confirmed_cases() {
    return tcc;
}
int Country::get_total_deaths() {
    return td;
}
int Country::get_total_recovered_cases() {
    return trc;
}

//destructor
Country::~Country() = default;

