#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <fstream> //using file I/O functions
#include <vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace serching_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Searching)
		{
			// TODO: Your test code here
			// TODO: Your test code here
			// Test insert file
			string filename = "abc.txt";
			ofstream out_stream; //ofstream is a class, out_stream is an object.
			out_stream.open(filename);

			ifstream in_stream; //ofstream is a class, in_stream is an object.
			in_stream.open(filename);

			// Test insert item
			out_stream << "1. abc" << endl;
			out_stream << "2. def" << endl;
			out_stream << "3. efg" << endl;


			// Test searching
			string a = "abc";
			vector<string> stringVec;
			string name = "search ab";
			ifstream readFile(filename);
			bool index = false;
			string readSentence;
			string keyword = name.substr(7);
			cout << "The key word is \"" << keyword << "\"" << endl;
			cout << "Here is/are the searching result: " << endl;

			int stringLength1 = 0;
			while (keyword[stringLength1] != '\0')
				stringLength1++;

			int stringLength2 = 0;
			while (readSentence[stringLength2] != '\0')
				stringLength2++;


			while (getline(readFile, readSentence)){
				stringLength2 = 0;
				while (readSentence[stringLength2] != '\0')
					stringLength2++;

				// if nothing can be found in txt file, skill the seaching part.
				if (readSentence == "" || readSentence == "\n")
					break;

				if (stringLength1 > stringLength2)
					continue;


				index = false;
				for (int i = 0; i < stringLength2 - stringLength1 + 1; i++)
				if (keyword == readSentence.substr(i, stringLength1))
					index = true;

				if (index == 1)
					stringVec.push_back(readSentence.substr(3));
			}

			//if the file can be created, line can be inserted and search result is workable, the result is positive.
			string b = stringVec[0];
			cout << a << endl;
			cout << b << endl;
			Assert::AreEqual(a, b);
		}

	};
}