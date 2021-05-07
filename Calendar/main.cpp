#include <set>
#include <map>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
#include "date.h"
#include "node.h"
#include "condition_parser.h"
#include "database.h"
#include "test_runner.h"
#include "output.h"


string ParseEvent(istream& is) {
	is >> ws;
	string answer;
	getline(is,answer);
  return answer;
}

void TestAll();

int main() {

	TestAll();

	Database db;

	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add") {
			string date_str;
			is >> date_str;
			const auto date = ParseDate(date_str);
			const auto event = ParseEvent(is);
			db.AddEvent(date, event);
		} else if (command == "Print") {
			auto entries = db.Print();
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
		} else if (command == "Del") {
			auto condition = ParseCondition(is); 
			int count = db.DeleteIf(condition);
			cout << "Removed " << count << " entries" << endl;
		} else if (command == "Find") {
			auto condition = ParseCondition(is);
			const auto entries = db.FindIf(condition);
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;

		} else if (command == "Last") {
			try {
			string date_str;
			is >> date_str;
			cout << db.Last(ParseDate(date_str)) << endl;
			} catch (invalid_argument&) {
				cout << "No entries" << endl;
			}
		} else if (command.empty()) {
			continue;
		} else {
			throw logic_error("Unknown command: " + command);
		}
	}

	return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
