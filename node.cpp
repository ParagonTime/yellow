#include "node.h"

Node::Node() {}

EmptyNode::EmptyNode() {}

template<class C>
bool ReturnComparis(const C& lft, const C& rht, const Comparison& cmp)
{
	switch (cmp)
	{
	case Comparison::Less:
		return lft < rht;
	case Comparison::LessOrEqual:
		return lft <= rht;
	case Comparison::Equal:
		return lft == rht;
	case Comparison::GreaterOrEqual:
		return  lft >= rht;
	case Comparison::Greater:
		return lft > rht;
	case Comparison::NotEqual:
		return lft != rht;
	default:
		throw logic_error("EventComparisonNode Evaluate");
	}
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
	return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& opr,
	const shared_ptr<Node>& left, const shared_ptr<Node>& right) :
	_opr(opr), _lft(left), _rht(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
	if (_opr == LogicalOperation::And)
	{
		return _lft->Evaluate(date, event) && _rht->Evaluate(date, event);
	}
	else
	{
		if (_opr == LogicalOperation::Or)
		{
			return _lft->Evaluate(date, event) || _rht->Evaluate(date, event);
		}
		else
		{
			throw logic_error("LogicalOperationNode Evaluate");
		}
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) :
	_cmp(cmp), _event(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
	return ReturnComparis(event, _event, _cmp);
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) :
	_cmp(cmp), _date(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
	return ReturnComparis(date, _date, _cmp);
}