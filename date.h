#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Date
{
public:
	Date();

	Date(const int& year, const int& mounth, const int& day);
	
	int GetYear() const;

	int GetMounth() const;

	int GetDay() const;

	string DateToPrint() const;

private:
	int year_;
	int mounth_;
	int day_;
};

bool operator<(const Date& lft, const Date& rht);

bool operator>(const Date& lft, const Date& rht);

bool operator==(const Date& lft, const Date& rht);

bool operator<=(const Date& lft, const Date& rht);

bool operator>=(const Date& lft, const Date& rht);

bool operator!=(const Date& lft, const Date& rht);

Date ParseDate(istream & is);

ostream& operator<<(ostream& os, const Date& date);