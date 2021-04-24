#ifndef match_information_H
#define match_information_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
class match_information
{
public:
    std::string team_one;
    std::string team_two;
    unsigned int hour;
    unsigned int minutes;
    unsigned int day;
    unsigned int month;
    unsigned int year;
    match_information();
    friend std::ostream &operator<<(std::ostream &out, const match_information &obj);
    friend std::istream &operator>>(std::istream &in, match_information &obj);
};
std::ostream &operator<<(std::ostream &out, const match_information &obj);
std::istream &operator>>(std::istream &in, match_information &obj);
#endif