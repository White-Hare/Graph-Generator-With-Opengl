#ifndef  MTREADER_H
#define MTREADER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef struct dstring {
	std::string first;
	std::string second;
} doublestring;

class MTR {
	std::string data;
	std::vector<std::string>  vecstr;
	
	
	std::fstream file;
	const char* filename;

public:
	std::vector <std::string>  vecmem;
	std::vector <std::vector<std::string> > veccon;
	MTR(const char *FileName);
	~MTR();

	const char *converttochar();
	std::vector <std::string> datavec();
	bool twoDsave (doublestring*);
	bool twoDsave(std::vector<std::vector<std::string> >);
	bool vectorsave(std::vector<std::string>);
	std::vector <std::string> Replace(std::vector <std::string>  , std::string word, std::string replacement);
	std::vector <std::vector<std::string> > Replace(std::vector <std::vector<std::string> >, std::string word, std::string replacement);
	std::vector <std::string> Replace(std::vector <std::string>  , int number, std::string replacement);
};

#endif // ! MTREADER_H
