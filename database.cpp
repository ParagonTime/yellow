#include "database.h"

Database::Database() {}

ostream& operator<<(ostream& os, const pair<Date, string>& pairr)
{
	os << pairr.first << " " << pairr.second;

	return os;
}

void Database::Add(const Date& date, const string& event)
{
	if (base_[date].count(event) == 0)
	{
		base_[date].insert(event);
		date_last_event[date].push_back(event);
	}
}

void Database::Print(ostream& out) const 
{
	for (const auto& i : date_last_event)
	{
		for (const auto& j : i.second)
		{
			out << i.first << " " << j << endl;
		}
	}
}

string Database::Last(const Date& date) const
{
	if (date_last_event.empty())
	{
		throw invalid_argument("empty");
	}
	else
	{
		auto it = date_last_event.upper_bound(date);
		if (it == date_last_event.begin())
		{
			throw invalid_argument("no ent");
		}
		else
		{
			--it;
			return it->first.DateToPrint() + " " + it->second.back();
		}
	}
}