#pragma once

#include <string>
#include <memory>

#include "date.h"

enum class LogicalOperation{
	And,
	Or,
};

enum class Comparison{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

class Node{
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
	virtual ~Node(){}
};

class EmptyNode : public Node{
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node{
public:
	DateComparisonNode(Comparison cmp,const Date& date) : _date(date), _cmp(cmp){}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	Date _date;
	Comparison _cmp;
};

class EventComparisonNode : public Node{
public:
	EventComparisonNode(Comparison cmp,const string& value) : _value(value), _cmp(cmp){}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const string& _value;
	Comparison _cmp;
};


class LogicalOperationNode : public Node{
public:
	LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right) :
		_op(op), lhs(left), rhs(right){}
	bool Evaluate(const Date& date, const string& event) const override;
private:
	LogicalOperation _op;
	shared_ptr<Node> lhs;
	shared_ptr<Node> rhs;
};
