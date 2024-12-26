#include "SemantikAnalyzer.h"

vector<int> types;
int Line_Count2 = 2;
bool Iflag = false;
bool Dflag = false;

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
	s += n.children[1].data;
	s += " ";
	s += n.children[0].data;
	s += " 2 DECL";
	print(s);
}

void SemantikAnalyzer::Descriptions(Node& n)
{
	for (int i = 0; i < n.children.size(); i++)
	{
		Descr(n.children[i]);
		Line_Count2++;
	}
}

void SemantikAnalyzer::Descr(Node& n)
{
	string s;
	s += n.children[0].data;
	s += " ";
	int count = 0;
	for (int i = 0; i < n.children[0].children.size(); i++)
	{
		if (names_int.find(n.children[0].children[i].data) != names_int.end() || names_double.find(n.children[0].children[i].data) != names_double.end())
			Out_Error();
		if (n.children[0].data == "int" && names_int.find(n.children[0].children[i].data) == names_int.end() && names_double.find(n.children[0].children[i].data) == names_double.end())
		{
			names_int.insert(n.children[0].children[i].data);
			s += n.children[0].children[i].data;
			count++;
			s += " ";
		}
		else if (n.children[0].data == "double" && names_int.find(n.children[0].children[i].data) == names_int.end() && names_double.find(n.children[0].children[i].data) == names_double.end())
		{
			names_double.insert(n.children[0].children[i].data);
			s += n.children[0].children[i].data;
			count++;
			s += " ";
		}
	}
	count++;
	s += to_string(count);
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
		Line_Count2++;
	}
}

void SemantikAnalyzer::Op(Node& n, string& s)
{
	s += n.children[0].data;
	if (names_int.find(n.children[0].data) != names_int.end())
		types.push_back(3);
	else
		types.push_back(6);
	s += " ";
	for (int i = 0; i < n.children[1].children.size(); i++)
	{
		SimpleExpr(n.children[1].children[i], s);
	}
	s += n.children[1].data;
	Iflag = false;
	Dflag = false;
	types.clear();
	print(s);
	s.clear();
}

void SemantikAnalyzer::SimpleExpr(Node& n, string& s)
{
	if (n.data == "SimpleExpr")
	{
		if (n.children[0].data == "ID_NAME")
		{
			if (names_int.find(n.children[0].children[0].data) != names_int.end())
			{
				s += n.children[0].children[0].data;
				s += " ";
				types.push_back(3);
			}
			if (names_double.find(n.children[0].children[0].data) != names_double.end())
			{
				s += n.children[0].children[0].data;
				s += " ";
				types.push_back(6);
			}
		}
		else if (n.children[0].data == "INT_CONST" && types.size() > 0)
		{
			if (Dflag)
				Out_Error();
			else if (Iflag)
			{
				s += n.children[0].children[0].data;
				s += " ";
			}
			else
			{
				for (int i = 0; i < types.size(); i++)
				{
					if (types[i] != 3)
					{
						Out_Error();
					}
				}
				s += n.children[0].children[0].data;
				s += " ";
			}
		}
		else if(n.children[0].data == "DOUBLE_CONST" && types.size() > 0)
		{
			if (Iflag)
				Out_Error(); 
			else if (Dflag)
			{
				s += n.children[0].children[0].data;
				s += " ";
			}
			else
			{
				for (int i = 0; i < types.size(); i++)
				{
					if (types[i] != 6)
					{
						Out_Error();
					}
				}
				s += n.children[0].children[0].data;
				s += " ";
			}
		}
		else if (n.children[0].data == "(")
		{
			for (int i = 0; i < n.children[0].children.size(); i++)
			{
				SimpleExpr(n.children[0].children[i], s);
			}
		}
		else if (n.children[0].data == "itod" && types.size() > 0)
		{
			Iflag = true;
			s += n.children[0].data;
			s += " ";
			if (n.children[1].data == "(" && types[0] == 6)
			{
				SimpleExpr(n.children[1].children[0], s);
			}
			else
				Out_Error();
			if (n.children[2].data == ")")
			{
				if (types.size() > 1 && types[1] == 6)
					Out_Error();
				s += "call";
				s += " ";
			}
			else
				Out_Error();
		}
		else if(n.children[0].data == "dtoi" && types.size() > 0)
		{
			Dflag = true;
			s += n.children[0].data;
			s += " ";
			if (n.children[1].data == "(" && types[0] == 3)
			{
				SimpleExpr(n.children[1].children[0], s);
			}
			else
				Out_Error();
			if (n.children[2].data == ")")
			{
				if (types.size() > 1 && types[1] == 3)
					Out_Error();
				s += "call";
				s += " ";
			}
			else
				Out_Error();
		}
		else
			Out_Error();
	}
	else if (n.data == "+" || n.data == "-")
	{
		for (int i = 0; i < n.children.size(); i++)
		{
			if(types.size() != 0)
				for (int i = 0; i < types.size(); i++)
				{
					for (int j = 0; j < types.size(); j++)
						if (types[i] != types[j])
							Out_Error();
				}
			SimpleExpr(n.children[i], s);
		}
		if (types.size() != 0)
			for (int i = 0; i < types.size(); i++)
			{
				for (int j = 0; j < types.size(); j++)
					if (types[i] != types[j])
						Out_Error();
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
	s += n.children[1].data;
	s += " ";
	s += n.children[0].data;
	print(s);
}

void SemantikAnalyzer::print(string& s)
{
	cout << s << '\n';
}

void SemantikAnalyzer::Out_Error()
{
	ofstream out("error.txt", ios::app);
	out << "Semantic error in line " + to_string(Line_Count2) + '\n';
	out.close();
	exit(1);
}
