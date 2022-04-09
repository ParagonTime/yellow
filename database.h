#pragma once

#include "date.h"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}


ostream& operator<<(ostream& os, const pair<Date, string>& pairr);

class Database
{
public:

	Database();

	void Add(const Date& date, const string& event);

	void Print(ostream& out) const;

	string Last(const Date& date) const;

	template<class P>
	vector<pair<Date, string>> FindIf(const P& predicate) const 
	{
		vector<pair<Date, string>> v;
		for (auto beg = date_last_event.begin(); beg != date_last_event.end(); ++beg)
		{
			for (auto begEvent = beg->second.begin(); begEvent != beg->second.end(); ++begEvent)
			{
				if (predicate(beg->first, *begEvent))
				{
					v.push_back({ beg->first, *begEvent });
				}
			}
		}

		return v;
	}

	template<class P>
	int RemoveIf(const P& predicate);
	
private:
	map<Date, set<string>> base_;
	map<Date, vector<string>> date_last_event;
};



template<class P>
int Database::RemoveIf(const P& predicate)
{
	int CountDel = 0;

	
	map<Date, set<string>> newBase;
	map<Date, vector<string>> newDateLast;
	for (auto it = date_last_event.begin(); it != date_last_event.end();++it)
	{
		const auto newList = stable_partition(it->second.begin(), it->second.end(),
			[it, predicate](const auto& event){ return predicate(it->first, event); });
		const auto size1 = it->second.size();
		if (newList == it->second.end())
		{
			CountDel = CountDel + size1;
		}
		else
		{
			newBase[it->first] = set<string>(newList, it->second.end());
			newDateLast[it->first] = vector<string>(newList, it->second.end());
			CountDel += size1 - newBase[it->first].size();
		}

	}
	base_ = newBase;
	date_last_event = newDateLast;

	/*
	auto itLast = date_last_event.begin();
	for (auto it = base_.begin();
		it != base_.end();)
	{
		for (auto event = base_[it->first].begin(); event != base_[it->first].end();)
		{
			if (predicate(it->first, *event))
			{
				event = base_[it->first].erase(event);
				++CountDel;
			}
			else
			{
				++event;
			}
		}
		if (!it->second.size())
		{
			it = base_.erase(it);
		}
		else
		{
			++it;
		}

		if (itLast != date_last_event.end())
		{
			for (auto eventL = date_last_event[itLast->first].begin(); 
				eventL != date_last_event[itLast->first].end();)
			{
				if (predicate(itLast->first, *eventL))
				{
					eventL = date_last_event[itLast->first].erase(eventL);
				}
				else
				{
					++eventL;
				}
			}
			if (!itLast->second.size())
			{
				itLast = date_last_event.erase(itLast);
			}
			else
			{
				++itLast;
			}
		}
	}
	*/
	return CountDel;
}