#include "match_information.h"
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
match_information::match_information()
{
    team_one = "";
    team_two = "";
    hour = 0;
    minutes = 0;
    day = 0;
    month = 0;
    year = 0;
}
ostream &operator<<(ostream &out, const match_information &obj)
{

    out << "the first team: " << obj.team_one << endl;
    out << "the second team: " << obj.team_two << endl;
    out << "time: " << obj.hour << ":" << obj.minutes << endl;
    out << "date: " << obj.day << ":" << obj.month << ":" << obj.year << endl;
    out << "------------------------------------------------------------" << endl;
    return out;
}
istream &operator>>(istream &in, match_information &obj)
{
    in >> obj.team_one;
    in >> obj.team_two;
    in >> obj.hour;
    in >> obj.minutes;
    in >> obj.day;
    in >> obj.month;
    in >> obj.year;
    return in;
}