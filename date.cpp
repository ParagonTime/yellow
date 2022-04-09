#include "date.h"

#include <sstream>

Date::Date() {}

Date::Date(const int& year, const int& mounth, const int& day) :
    year_(year), mounth_(mounth), day_(day) {}

int Date::GetDay() const { return day_; }

int Date::GetMounth() const { return mounth_; }

int Date::GetYear() const { return year_; }

string Date::DateToPrint() const
{
    stringstream out;
    out << setfill('0') << setw(4) << 
       this->GetYear() << '-' << setw(2) <<
       this->GetMounth() << '-' << setw(2) <<
       this->GetDay();
    return out.str();
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.DateToPrint();
	return os;
}

bool operator<(const Date& lft, const Date& rht)
{
	return vector<int> { lft.GetYear(), lft.GetMounth(), lft.GetDay() } <
		vector<int> { rht.GetYear(), rht.GetMounth(), rht.GetDay()};
}

bool operator>(const Date& lft, const Date& rht)
{
    return vector<int> { lft.GetYear(), lft.GetMounth(), lft.GetDay() } >
        vector<int> { rht.GetYear(), rht.GetMounth(), rht.GetDay()};
}

bool operator==(const Date& lft, const Date& rht)
{
    return vector<int> { lft.GetYear(), lft.GetMounth(), lft.GetDay() } ==
        vector<int> { rht.GetYear(), rht.GetMounth(), rht.GetDay()};
}

bool operator<=(const Date& lft, const Date& rht)
{
    return vector<int> { lft.GetYear(), lft.GetMounth(), lft.GetDay() } <=
        vector<int> { rht.GetYear(), rht.GetMounth(), rht.GetDay()};
}

bool operator>=(const Date& lft, const Date& rht)
{
    return vector<int> { lft.GetYear(), lft.GetMounth(), lft.GetDay() } >=
        vector<int> { rht.GetYear(), rht.GetMounth(), rht.GetDay()};
}

bool operator!=(const Date& lft, const Date& rht)
{
    return vector<int> { lft.GetYear(), lft.GetMounth(), lft.GetDay() } !=
        vector<int> { rht.GetYear(), rht.GetMounth(), rht.GetDay()};
}

Date ParseDate(istream& is)
{

    int day, mounth, year;
    is >> year;
    is.ignore(1);
    //cout << day << " " << stoi(day) << endl;
    is >> mounth;
    is.ignore(1);
    //cout << mounth << " " << stoi(mounth) << endl;
    is >> day;
    //cout << year << " " << stoi(year) << endl; getline(os, day, '-');

    return Date(year, mounth, day);
}

