#include <iomanip>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>


using namespace std;
#include "date.h"
#include "node.h"
#include "database.h"
#include "output.h"

bool operator!= (const Date& lhs,const Date& rhs){
	return (lhs < rhs) || (rhs < lhs);
}
bool operator< (const pair<Date,string>& lhs,const pair<Date,string>& rhs){
	if (lhs.first != rhs.first){
		return lhs.first < rhs.first;
	} else {
		return lhs.second < rhs.second;
	}
}

void Database::AddEvent(const Date& date, const string& event) {
	if (!storage.count(date)){
		storage[date].push_back(event);
		return;
	}
	auto beg = storage.at(date).begin();
	auto end = storage.at(date).end();
	if (find(beg,end, event) == end){//Ò å íå äîáàâëÿåì îäèíàêîâûå
		storage[date].push_back(event);
	}
}

int Database::DeleteIf(shared_ptr<Node> node) {
	int delete_count = 0;

	for (auto It = storage.begin(); It != storage.end(); ++It){
		auto begin = stable_partition(It->second.begin(), It->second.end(),
				[node, It](string event){
					return !node->Evaluate(It->first, event);
				});
		size_t sz = It->second.end() - begin;
		It->second.erase(begin, It->second.end());
		return sz;
	}

	return delete_count;
}

set<pair<Date,string>> Database::FindIf(shared_ptr<Node> node) const {
	set<pair<Date,string>> answer; 
	for (auto& item : storage){
		for (const auto& event : item.second){
			if (node->Evaluate(item.first, event)){
				answer.insert(make_pair(item.first, event));
			}
		}
	}
	return answer;
}

set<pair<Date,string>> Database::Print() const {
	set<pair<Date,string>> answer;
	for (const auto& item : storage) {
		for (const string& event : item.second) {
			answer.insert(make_pair(item.first, event));
		}
	}
	return answer;

}

string Database::Last(const Date& date) const{
	auto It = storage.upper_bound(date);
	if (It == storage.begin()){
		throw invalid_argument("");
	} else {
		return (--It)->second.back();
	}
}
