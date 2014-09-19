#include "stdafx.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <fstream> //using file I/O functions
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;
namespace Sortingtest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Test insert file
			string filename = "abc.txt";

			ofstream out_stream;	//ofstream is a class, out_stream is an object.
			out_stream.open(filename);

			ifstream in_stream;		//ofstream is a class, in_stream is an object.
			in_stream.open(filename);

			// Test insert item without sorting
			out_stream << "1. def" << endl;
			out_stream << "2. abc" << endl;
			out_stream << "3. efg" << endl;

			// The expected result after sorting
			vector<string> stringResult{ "abc", "def", "efg" };

			// Create vector in order to store the data in vector
			vector<string> stringVec;
			ifstream readFile(filename);
			string readSentence;

			while (getline(readFile, readSentence)){
				if (readSentence == "" || readSentence == "\n")
					break;
				stringVec.push_back(readSentence.substr(3));
			}
			sort(stringVec.begin(), stringVec.end());

			//Compare all the colume of my expected result.
			for (int i = 0; i < stringVec.size(); i++)
				Assert::AreEqual(stringResult[i], stringVec[i]);
		}

	};
}