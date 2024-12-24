#include "SemantikAnalyzer.h"

void SemantikAnalyzer::sem_parse(Node& root)
{
	Begin(root.children[0]);
	Descriptions(root.children[1]);
	Operators(root.children[2]);
	End(root.children[3]);
}

void SemantikAnalyzer::Begin(Node& n)
{
	string s;
	s += n.children[0].data;
	s += " ";
	s += n.children[1].data;
	print(s);
}

void SemantikAnalyzer::Descriptions(Node& n)
{
	for (int i = 0; i < n.children.size(); i++)
		Descr(n.children[i]);
}

void SemantikAnalyzer::Descr(Node& n)
{
	string s;
	s += n.children[0].data;
	s += " ";
	for (int i = 0; i < n.children[0].children.size(); i++)
	{
		s += n.children[0].children[i].data;
		names.insert(n.children[0].children[i].data);
		s += " ";
	}
	s += to_string(n.children[0].children.size() + 1);
	s += " ";
	s += "DECL";
	print(s);
}

void SemantikAnalyzer::Operators(Node& n)
{
	string s;
	for (int i = 0; i < n.children.size(); i++)
	{
		Op(n.children[i], s);
		s += "\n";
	}
	print(s);
}

void SemantikAnalyzer::Op(Node& n, string& s)
{
	s += n.children[0].data;
	s += " ";
	for (int i = 0; i < n.children[1].children.size(); i++)
	{
		SimpleExpr(n.children[1].children[i], s);
	}
	s += n.children[1].data;
}

void SemantikAnalyzer::SimpleExpr(Node& n, string& s)
{
	if (n.data == "SimpleExpr")
	{
		if (n.children[0].data == "ID_NAME")
		{
			if (names.find(n.children[0].children[0].data) != names.end())
			{
				s += n.children[0].children[0].data;
				s += " ";
			}
		}
		else if (n.children[0].data == "INT_CONST" || n.children[0].data == "DOUBLE_CONST")
		{
			s += n.children[0].children[0].data;
			s += " ";
		}
		else if (n.children[0].data == "(")
		{
			for (int i = 0; i < n.children[0].children.size(); i++)
			{
				SimpleExpr(n.children[0].children[i], s);
			}
		}
		else if (n.children[0].data == "itod" || n.children[0].data == "dtoi")
		{
			s += n.children[0].data;
			s += " ";
			if (n.children[1].data == "(")
			{
				SimpleExpr(n.children[1].children[0], s);
			}
			if (n.children[2].data == ")")
			{
				s += "call";
				s += " ";
			}
		}
		else
			Out_Error();
	}
	else if (n.data == "+" || n.data == "-")
	{
		for (int i = 0; i < n.children.size(); i++)
		{
			SimpleExpr(n.children[i], s);
		}
		s += n.data;
		s += " ";
	}
	else
		Out_Error();
}

void SemantikAnalyzer::End(Node& n)
{
	string s;
	s += n.children[0].data;
	s += " ";
	s += n.children[1].data;
	print(s);
}

void SemantikAnalyzer::print(string& s)
{
	cout << s << '\n';
}

void SemantikAnalyzer::Out_Error()
{
	ofstream out("error.txt", ios::app);
	out << "Semantic error\n";
	out.close();
	exit(1);
}