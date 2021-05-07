#pragma once

class Database {
public:
	void AddEvent(const Date& date, const string& event);

	int DeleteIf(shared_ptr<Node> node);

	set<pair<Date,string>> FindIf(shared_ptr<Node> node) const;

	set<pair<Date,string>> Print() const;

	string Last(const Date& date) const;
private:
	map<Date, vector<string>> storage;
};



