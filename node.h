#pragma once
#include "date.h"
#include <memory>

enum class LogicalOperation
{
	Or,
	And,
};

enum class Comparison
{
	Less,						//   "<"
	LessOrEqual,				//   "<="
	Greater,					//   ">"
	GreaterOrEqual,				//   ">="
	Equal,						//   "=="
	NotEqual,					//   "!="
};

class Node 
{
public:
	Node();

	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node 
{
public:
	EmptyNode();

	bool Evaluate(const Date& date, const string& event) const override;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& opr,
		const shared_ptr<Node>& left, const shared_ptr<Node>& right);

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const LogicalOperation _opr;
	const shared_ptr<Node> _lft;
	const shared_ptr<Node> _rht;
};

class EventComparisonNode : public Node
{
public:

	EventComparisonNode(const Comparison& cmp, const string& event);
	
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison _cmp;
	const string _event;

};

class DateComparisonNode : public Node
{
public:

	DateComparisonNode(const Comparison& cmp, const Date& date);

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison _cmp;
	const Date _date;
};

