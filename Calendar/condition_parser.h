#pragma once
using namespace std;

#include <memory>
#include <iostream>


#include "node.h"

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
