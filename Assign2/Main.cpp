// Assign2_2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

string dir = "C:\\Users\\Lachlan\\source\\repos\\Assign2\\Assign2\\";

string FNAME1 = "A2Part1a.txt";
string FNAME1e = "A2Part1err.txt";
string FNAME2 = "A2Part2a.txt";
string FNAME2e = "A2Part2err.txt";
string FNAME3 = "A2Part3a.txt";
string FNAME3e = "A2Part3err.txt";
string FNAME4 = "A2Part4a.txt";
string FNAME4e = "A2Part4err.txt";
string FNAME5 = "A2Part5a.txt";
string FNAME5e = "A2Part5err.txt";
string FNAMET = "A2Test.txt";

string fileName = "";

bool debug1 = false;
bool debug2 = false;
bool debug3 = false;
bool debug4 = false; // trace 
bool debug5 = false; // around = 

vector<string> inVec = {};
map<string, float> outMap = {};

string errGlobal = "";
bool hasError = false;
int errLineNum = 0;
string errLine = "";






std::string trim(const std::string& str,
	const std::string& whitespace = " \t")
{
	// from h ttps://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
	//
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

void readFileVec(string fileNameZ, vector<string>& inVec)
{
	fileName = fileNameZ;
	inVec.clear();

	std::ifstream myFile(fileName);
	if (!myFile.is_open())
	{
		cout << "Error File not found ->" << fileName << "<-\n\n";
		return;
	}

	std::string str;

	int i = 0;
	while (std::getline(myFile, str))
	{
		if (debug1) cout << "DEBUG1 -line " << ++i << " is:" << str << endl;
		str = trim(str);
		//if (str[0] == '/') continue;
		inVec.push_back(str);
	}

}

void showVector(vector<string>& vec)
{
	int i = 0;
	cout << "\nThis is the input file\n";
	cout << "----------------------\n";
	for (string s : vec)
	{
		cout << "line " << ++i << " is:" << s << endl;
	}
	cout << "\n";
}


void showMap(map<string, float>& m)
{
	int i = 0;
	map<string, float>::iterator iter;  // construct an iterator
	cout << "\n";
	cout << "These are the variables at the end of the run\n";
	cout << "---------------------------------------------\n";
	for (iter = m.begin(); iter != m.end(); ++iter) // these should be sorted
	{
		cout << "m[" << iter->first << "]=" << iter->second << '\n';
	}
	cout << "\n";
}

void doP6(vector<string>& inVec, map<string, float>& outMap)
{

}

void doP5(vector<string>& inVec, map<string, float>& outMap)
{
	outMap.clear();
	cout << "This is the result of the P5 run\n";
	cout << "--------------------------------\n";

}

float evaluteP5(string s) {

}

void doP4(vector<string>& inVec, map<string, float>& outMap)
{
	cout << "This is the result of the P4 run\n";
	cout << "--------------------------------\n";


	for (int i = 0; i < inVec.size(); i++) {
		string s = inVec.at(i);
		s = trim(s);

		string leftBit = "";
		string rightBit = "";

		int count = 0;
		int place = -1;

		int comment = s.find("//");
		if (comment != -1) {
			//This is a comment
		}

		while (count < s.size()) {
			if (s[count] == '=') {
				place = count; break; 
			}
			count++; 
		}

			string leftBit = s.substr(0, count);
			string rightBit = s.substr(count + 1, s.size() - count);

			string l = leftBit;
			outMap[l] = evaluteP5(rightBit);
	}
}


float Evalute(string tok, float total, bool isPlus, int i) {
	bool key = outMap.count(tok);
	if (key == true) {
		if (isPlus == true) {
			total = total + outMap[tok];
		}
		else {
			total = total - outMap[tok];
		}
	}
	else {
		try {
			if (stof(tok) != 0) {
				if (isPlus == true) {
					total = total + stof(tok);
				}
				else {
					total = total - stof(tok);
				}
			}
		}
		catch (...) {
			cout << "Error: Invalid  " << endl;
			cout << "   In line " << i << endl;
			tok = "";
		}
	}
	return total;
}


void doP3(vector<string>& inVec, map<string, float>& outMap)
{
	cout << "This is the result of the P3 run\n";
	cout << "--------------------------------\n";


	for (int i = 0; i < inVec.size(); i++) {
		string s = inVec.at(i);
		s = trim(s);

		float total = 0;
		bool isPlus = true;
		bool isChar = false;

		string thingToShow = "";
		// now advance the character pointer called cp
		int cp = 0;
		string tok = "";

		int comment = s.find("//");
		if (comment != -1) {
			//This is a comment
		}
		else {
			while (cp < s.size()) {
				char c = s[cp];

				if (c == '+') {
					if (tok != "") {
						total = Evalute(tok, total, isPlus, i);
						isPlus = true;
						tok = "";
					}
					else {
						cout << "Missing or Wrong Operator " << endl;
						cout << "   in line number: " << i << endl;
					}
				}

				else if (c == '-') {
					if (tok != "") {
						total = Evalute(tok, total, isPlus, i);
						isPlus = false;
						tok = "";
					}
					else {
						cout << "Missing or Wrong Operator " << endl;
						cout << "   in line number: " << i << endl;
					}
				}

				else
				{
					// build token
					tok = tok + c;
				}
				cp++;
			}

			if (tok != "") {
				total = Evalute(tok, total, isPlus, i);
				cout << "expression " << s << " gives " << total << endl;
			}
			else {
				cout << "Missing or Wrong Operator " << endl;
				cout << "   in line number: " << i << endl;
			}
		}
	}

}

void doP2(vector<string>& inVec, map<string, float>& outMap)
{
	cout << "This is the result of the P2 run\n";
	cout << "--------------------------------\n";

	for (int i = 0; i < inVec.size(); i++) {
		string s = inVec.at(i);
		s = trim(s);

		float total = 0;
		bool isPlus = true;

		string thingToShow = "";
		// now advance the character pointer called cp
		int cp = 0;
		string tok = "";

		int comment = s.find("//");
		if (comment != -1) {
			//This is a comment
		}
		else{
			while (cp < s.size()) {
				char c = s[cp];

				if (c == '+') {
					if (tok != "") {
						if (isPlus == true) {
							total = total + stof(tok);
						}
						else {
							total = total - stof(tok);
						}
						isPlus = true;
						tok = "";
					}
					else {
						cout << "Missing or Wrong Operator " << endl;
						cout << "   in line number: " << i << endl;
					}
				}

				else if (c == '-') {
					if (tok != "") {
						if (isPlus == true) {
							total = total + stof(tok);
						}
						else {
							total = total - stof(tok);
						}
						isPlus = false;
						tok = "";
					}
					else {
						cout << "Missing or Wrong Operator " << endl;
						cout << "   in line number: " << i << endl;
					}
				}

				else
				{
					// build token
					tok = tok + c;
				}
				cp++;
			}

			if (tok != "") {
				if (isPlus == true) {
					total = total + stof(tok);
				}
				else {
					total = total - stof(tok);
				}

				cout << "expression " << s << " gives "<< total << endl;
			}
			else {
				cout << "Missing or Wrong Operator " << endl;
				cout << "   in line number: " << i << endl;
			}
		}
	}
}

void doP1(vector<string>& inVec, map<string, float>& outMap)
{
	outMap.clear();
	cout << "This is the result of the P1 run\n";
	cout << "--------------------------------\n";
	cout << "(No output except errors it just sets the values)\n";
	
	
	for (int i = 0; i < inVec.size(); i++) {
		string s = inVec.at(i);
		s = trim(s);

		int comment = s.find("//");
		int whereP = s.find("=");
		if (comment != -1) {
			//This is a comment
		}
		else if (whereP == -1)
		{
			cout << "Error: Missing Equals '=' " << endl;
			cout << "Error: In Line " << i << endl;
			cout << "Error Line:" << s << endl;
		}
		else {
			string leftBit = s.substr(0, whereP);
			string rightBit = s.substr(whereP + 1, s.size() - whereP);
			string l = leftBit;
			outMap[l] = stof(rightBit);
		}
	}
}



int main()
{
	std::cout << "ST2 Assigment2 \n";

	FNAME1 = dir + FNAME1; // "A2Part1a.txt";
	FNAME1e = dir + FNAME1e; // "A2Part1err.txt";
	FNAME2 = dir + FNAME2; // "A2Part2a.txt";
	FNAME2e = dir + FNAME2e; // "A2Part2err.txt";
	FNAME3 = dir + FNAME3; // "A2Part3a.txt";
	FNAME3e = dir + FNAME3e; // "A2Part3err.txt";
	FNAME4 = dir + FNAME4; // "A2Part4a.txt";
	FNAME4e = dir + FNAME4e; //"A2Part4err.txt";
	FNAME5 = dir + FNAME5; // "A2Part5a.txt";
	FNAME5e = dir + FNAME5e; // "A2Part5err.txt";
	FNAMET = dir + FNAMET; // "A2Test.txt";

	string opt = " ";
	while (toupper(opt[0]) != 'E')
	{
		std::cout << "Assign2 2021 Menu\n";
		if (debug4) std::cout << "Debug trace on\n";
		std::cout << "E(xit) -   Exit\n";
		std::cout << "P1  - Create map of values \n";
		std::cout << "P1e - Create map of values (with error input) \n";
		std::cout << "P2  - Parse Strings  \n";
		std::cout << "P2e - Parse Strings  (with error input)\n";
		std::cout << "P3  - Parse Strings including variables  \n";
		std::cout << "P3e - Parse Strings including variables (with Errors) \n";
		std::cout << "P4  - Make them statements with an =   \n";
		std::cout << "P4e - Make them statements with an = (with Errors) \n";
		std::cout << "P5  - Add divide and multiply  \n";
		std::cout << "P5e - Add divide and multiply  (with Errors)\n";
		std::cout << "T   - Temporary for testing (not part of assessment)\n";
		std::cout << "D   - set unset debug4  (not part of assessment)\n";
		// std::cout << "M1   - Run file A2Part1m.txt\n";
		// std::cout << "M2   - Run file A2Part2m.txt\n";
		// std::cout << "M3   - Run file A2Part3m.txt\n";
		// std::cout << "M4   - Run file A2Part4m.txt\n";
		// std::cout << "M5   - Run file A2Part5m.txt\n";

		cin >> opt;
		std::cout << "Option selected:" << opt << endl;
		for (auto& c : opt) c = toupper(c);

		if (opt == "P1") { readFileVec(FNAME1, inVec); showVector(inVec); doP1(inVec, outMap); showMap(outMap); }
		if (opt == "P1E") { readFileVec(FNAME1e, inVec); showVector(inVec); doP1(inVec, outMap); showMap(outMap); }
		if (opt == "P2") { readFileVec(FNAME2, inVec); showVector(inVec); doP2(inVec, outMap); showMap(outMap); }
		if (opt == "P2E") { readFileVec(FNAME2e, inVec); showVector(inVec); doP2(inVec, outMap); showMap(outMap); }
		if (opt == "P3") { readFileVec(FNAME3, inVec); showVector(inVec); doP3(inVec, outMap); showMap(outMap); }
		if (opt == "P3E") { readFileVec(FNAME3e, inVec); showVector(inVec); doP3(inVec, outMap); showMap(outMap); }
		if (opt == "P4") { readFileVec(FNAME4, inVec); showVector(inVec); doP4(inVec, outMap); showMap(outMap); }
		if (opt == "P4E") { readFileVec(FNAME4e, inVec); showVector(inVec); doP4(inVec, outMap); showMap(outMap); }
		if (opt == "P5") { readFileVec(FNAME5, inVec); showVector(inVec); doP5(inVec, outMap); showMap(outMap); }
		if (opt == "P5E") { readFileVec(FNAME5e, inVec); showVector(inVec); doP5(inVec, outMap); showMap(outMap); }
		if (opt == "T") { readFileVec(FNAMET, inVec); showVector(inVec); doP1(inVec, outMap); showMap(outMap); }
		if (opt == "D") debug4 = !debug4;
		//if (opt == "M1")  // example for students
		//{ 
		//	FNAME1 = dir + "A2Part1m.txt";
		//	readFileVec(FNAME1, inVec); showVector(inVec); doP1(inVec, outMap); showMap(outMap); 
		//}

		std::cout << endl;
	}
	std::cout << "Program Exits\n";
}

