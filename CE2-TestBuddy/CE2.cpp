// I usually save my work to the disk when I finish a small part of my program.
// In this program, I save my works during completing a sub-task, e.g. 'delete' and 'add' function.
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <fstream> //using file I/O functions
#include <vector>


using namespace std;

int stringLength(string str){
	int length = 0;
	while (str[length] != '\0')
		length++;
	return length;
}

void addLine(ofstream& out_stream, int& numOfItems, string name, string filename){
	out_stream << numOfItems << ". " << name.substr(4) << endl;
	numOfItems++;
	cout << "added to " << filename << ".txt: \"" << name.substr(4) << "\"" << endl;
}

void clear(string filename, int& numOfItems){
	ofstream out_stream; //ofstream is a class, out_stream is an object.
	out_stream.open(filename);

	ifstream in_stream; //ofstream is a class, in_stream is an object.
	in_stream.open(filename);

	cout << "all content deleted from " << filename << endl;
	numOfItems = 1;
}

void add(ofstream out_stream, int& numOfItems, string name, string filename){
	out_stream << numOfItems << ". " << name.substr(4) << endl;
	numOfItems++;
	cout << "added to " << filename << ".txt: \"" << name.substr(4) << "\"" << endl;
}

void display(string filename){
	ifstream readFile(filename);
	string readSentence;
	int noOfSentence = 0;

	while (getline(readFile, readSentence)){
		// if nothing can be found in txt file, skill the seaching part.
		if (noOfSentence == 0 && (readSentence == "" || readSentence == "\n"))
			break;
		cout << readSentence << endl;
		noOfSentence++;
	}

	//message of empty file.
	if (noOfSentence == 0)
		cout << filename << " is empty" << endl;
}


template <typename Temp>
void print_vector(vector<Temp> &vec){
	typename vector<Temp>::iterator iter;
	int num = 1;
	for (iter = vec.begin(); iter != vec.end(); ++iter){
		cout << num << ". " << *iter << endl;
		num++;
	}
}

void search(string filename, string name){
	vector<string> stringVec;
	ifstream readFile(filename);
	bool index = false;
	string readSentence;
	string keyword = name.substr(7);
	cout << "The key word is \"" << keyword << "\"" << endl;
	cout << "Here is/are the searching result: " << endl;
	int keywordLength = stringLength(keyword);

	while (getline(readFile, readSentence)){
		// if nothing can be found in txt file, skill the seaching part.
		if (readSentence == "" || readSentence == "\n")
			break;

		if (keywordLength > stringLength(readSentence))
			continue;

		index = false;

		for (int i = 0; i < stringLength(readSentence) - keywordLength + 1; i++)
		if (keyword == readSentence.substr(i, stringLength(keyword)))
			index = true;

		if (index == 1)
			stringVec.push_back(readSentence.substr(3));
	}
	print_vector(stringVec);
}


void deleteLine(ifstream& in_stream, string filename, string name){
	// create a 'replace.txt' to store the temporary data, except the sentence that we don't want.
	ofstream out_stream1;
	out_stream1.open("replace.txt");

	ifstream in_stream1;
	in_stream1.open(filename);

	string readout;
	string search;

	int increment = 1;

	// detect which sentence should be deleted.
	while (getline(in_stream, readout)){
		if (readout[0] == name[7])
			out_stream1 << "";
		else{
			// each sentence should be assigned to the corresponding number lable
			out_stream1 << increment << '.' << " " << readout.substr(3) << endl;
			increment++;
		}
	}

	out_stream1.close();
	in_stream1.close();

	//remove the origin file.
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	//copy the content from replace.txt to the original txt file
	ofstream out_stream2;
	out_stream2.open(filename);
	ifstream in_stream2;
	in_stream2.open("replace.txt");

	while (getline(in_stream2, readout)){
		out_stream2 << readout << endl;
	}
}

int main()
{
	//used to get file name and the words needed to be placed on a txt file
	string filename;

	//used to get the user input the document name
	string line;

	//used to identify the number of each user input.
	int numOfItems = 1;

	//used to get the user input the input sentences.
	string name;

	getline(cin, line);

	// find the second word of the user input and set it as the file name of the .txt file.=
	unsigned int tStart = 0, tEnd = 0;

	tStart = line.find_first_of(" ");
	tEnd = line.find_first_of(" ", tStart + 1);
	filename = line.substr(tStart, tEnd);

	ofstream out_stream; //ofstream is a class, out_stream is an object.
	out_stream.open(filename);

	ifstream in_stream; //ofstream is a class, in_stream is an object.
	in_stream.open(filename);

	cout << "Welcome to TextBuddy. " << filename << " is ready for use" << endl;

	while (true)
	{
		cout << "Comment: ";
		getline(cin, name);


		// test the first word of each input and determine what the task should do.
		if (name.substr(0, 3) == "add" || name.substr(0, 3) == "ADD" || name.substr(0, 3) == "Add")
			addLine(out_stream, numOfItems, name, filename);

		// import each sentence from the file and display it.
		else if (name.substr(0, 7) == "display" || name.substr(0, 7) == "DISPLAY" || name.substr(0, 7) == "Display")
			display(filename);

		// clear the content of the text file.
		else if (name.substr(0, 5) == "clear" || name.substr(0, 5) == "Clear" || name.substr(0, 5) == "CLEAR")
			clear(filename, numOfItems);

		else if (name.substr(0, 4) == "exit" || name.substr(0, 4) == "Exit" || name.substr(0, 4) == "EXIT")
			return 0;

		else if (name.substr(0, 6) == "delete" || name.substr(0, 6) == "Delete" || name.substr(0, 6) == "DELETE")
			deleteLine(in_stream, filename, name);

		else if (name.substr(0, 6) == "search" || name.substr(0, 6) == "Search" || name.substr(0, 6) == "SEARCH")
			search(filename, name);

		else
			cout << "Input Error. Please enter again" << endl;


	}


	system("pause");
}