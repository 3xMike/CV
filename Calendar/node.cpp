#include <string>
#include <memory>

using namespace std;
#include "date.h"
#include "node.h"


bool EmptyNode::Evaluate(const Date& date, const string& event) const{
	return true;
}


bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less){
		return date < _date; 
	} else if (_cmp == Comparison::LessOrEqual){
		return !(date > _date);
	} else if (_cmp == Comparison::Greater){
		return date > _date;
	} else if (_cmp == Comparison::GreaterOrEqual){
		return !(date < _date);
	} else if (_cmp == Comparison::Equal){
		return date == _date;
	} else {
		return !(date == _date);
	}
}


bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less){
		return event < _value; 
	} else if (_cmp == Comparison::LessOrEqual){
		return event <= _value;
	} else if (_cmp == Comparison::Greater){
		return event > _value;
	} else if (_cmp == Comparison::GreaterOrEqual){
		return event >= _value;
	} else if (_cmp == Comparison::Equal){
		return event == _value;
	} else {
		return event != _value;
	}
}


bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if (_op == LogicalOperation::Or) {
		return lhs->Evaluate(date,event) || rhs->Evaluate(date,event);
	} else {
		return lhs->Evaluate(date,event) && rhs->Evaluate(date,event);
	}
}


