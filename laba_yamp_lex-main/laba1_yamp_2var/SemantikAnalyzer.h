#pragma once
#include <iostream>
#include <string>
#include <set>
#include "Node.h"

using namespace std;

class SemantikAnalyzer
{
public:
	set<string> names;
	void sem_parse(Node& root);
	void Begin(Node& n);
	void End(Node& n);
	void Descriptions(Node& n);
	void Descr(Node& n);
	void SimpleExpr(Node& n, string& s);
	void Operators(Node& n);
	void Op(Node& n, string& s);
	void print(string& s);
	void Out_Error();
private:
	
};