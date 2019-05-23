#pragma warning(disable:4996)
#include"MTReader.h"
#include<string.h>
#include <sstream>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;



MTR::MTR(const char *FileName) {
	file.exceptions(fstream::failbit | fstream::badbit);// ensures ifstream objects can throw exceptions:

	try {
		file.open(FileName);

		filename = FileName;

		stringstream fileStream;

		fileStream << file.rdbuf();

		data = fileStream.str();
		file.close();
	}
	catch (fstream::failure e) {
		cerr << "File hasn't been readed succesfully" << endl;
	}

}

MTR::~MTR() {
	//fill it later
}

const char* MTR::converttochar() {
	const char *ch;
	ch = new char[data.length() + 1];
	ch = data.c_str();



	return ch;
}

std::vector <std::string> MTR::datavec() {

	char *ch = new char[data.length() + 1];
	strcpy(ch, data.c_str());

	int i = 0, i2 = 0;
	char* column = strtok_s(ch, ":", &ch);

	string holder, members;
	while (column != NULL) {
		holder = column;
		holder.erase(remove(holder.begin(), holder.end(), ' '), holder.end());//delete white spaces


		if (holder != " " && holder != "\n" && sizeof(holder) != 0) {

			veccon.push_back(vector<string>());//add a empty row

			if (holder.find("{") != string::npos) {

				char* row = strtok_s(column, ",", &column);
				while (row != NULL) {

					members = row;
					members.erase(remove(members.begin(), members.end(), ' '), members.end());
					members.erase(remove(members.begin(), members.end(), '{'), members.end());
					members.erase(remove(members.begin(), members.end(), '}'), members.end());

					vecmem.push_back(members);

					veccon[i].push_back(members);

					row = strtok_s(column, ",", &column);
					//cout << veccon[i][i2] << endl;
					i2++;
				}
				i2 = 0;
				column = strtok_s(ch, ":", &ch);


			}

			else {

				veccon[i].push_back(holder);
			}
			vecstr.push_back(holder);//find a way for gettin together vecmem and vecstr
									 //cout <<holder <<i++<< endl;
			i++;
		}


		column = strtok_s(ch, ":", &ch);


	}


	return vecstr;

}

bool MTR::twoDsave(doublestring *dstr) {
	bool saved = false;

	try {
		file.open(filename, ios::trunc | ios::out);

		for (int i = 0; i < vecstr.size() / 2; i++) {
			file << ":" << dstr[i].first << ":" << dstr[i].second << ":" << endl;
		}
		saved = true;
	}
	catch (ifstream::failure e) {
		cerr << "Error: Save wasn't succesfull" << endl;
	}

	file.close();
	return saved;
}

bool MTR::twoDsave(std::vector<std::vector<std::string> > veccon) {
	bool saved = false;

	try {
		file.open(filename, ios::trunc | ios::out);

		for (int i = 0; i < veccon.size(); i++) {
			for (int i2 = 0; i2 < veccon[i].size(); i2++) {
				if (veccon[i].size() == 1)
					file << ':' << veccon[i][i2] << ':';

				else if (i2 == 0 && veccon[i].size() != 1)
					//cout << "hello" << endl;
					file << "{" << veccon[i][i2];
				else if (i2 == veccon[i].size() - 1 && veccon[i].size() != 1)
					file << ',' << veccon[i][i2] << "}:";

				else
					file << ',' << veccon[i][i2];
			}
			if (i % 2 == 1) {
				file << endl;
			}
		}
		saved = true;
	}
	catch (ifstream::failure e) {
		cerr << "Error: Save wasn't succesfull" << endl;
	}

	file.close();

	return saved;


}

bool MTR::vectorsave(vector<string> vec) {
	bool saved = false;

	try {
		file.open(filename, ios::trunc | ios::out);

		for (int i = 0; i < vecstr.size(); i++) {
			file << ":" << vec[i] << ":" << endl;
		}
		saved = true;
	}
	catch (ifstream::failure e) {
		cerr << "Error: Save wasn't succesfull" << endl;
	}

	file.close();
	return saved;
}


std::vector <std::string> MTR::Replace(vector <std::string>  destination, string word, string replacement) {
	bool saved = false;
	int i = 0;

	//replace(destination.begin(), destination.end(),word ,replacement); //alternativly
	for (; i < destination.size(); i++) {
		if (destination[i] == word) {
			cout << "\"" << destination[i] << "\" is replaced with ";
			cout << "\"" << replacement << "\"" << endl;

			destination[i] = replacement;

			saved = true;
		}

	}

	if (saved != true) {
		cerr << "Error: Word Didn't found" << endl;
	}

	return destination;
}

std::vector <std::vector<std::string> > MTR::Replace(std::vector <std::vector<std::string> > destination, std::string word, std::string replacement) {
	bool saved = false;


	//replace(destination.begin(), destination.end(),word ,replacement); //alternativly
	for (int i = 0; i < destination.size(); i++) {
		for (int i2 = 0; i2<destination[i].size(); i2++) {
			if (destination[i][i2] == word) {
				cout << "\"" << destination[i][i2] << "\" is replaced with ";
				cout << "\"" << replacement << "\"" << endl;

				destination[i][i2] = replacement;
				saved = true;
			}

		}

	}

	if (saved != true) {
		cerr << "Error: Word Didn't found" << endl;
	}

	return destination;


}

std::vector <std::string> MTR::Replace(vector <std::string>  destination, int number, string replacement) {
	bool saved = false;

	destination[number] = replacement;


	return destination;
}


