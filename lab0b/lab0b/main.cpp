#include <iostream>
#include <string>

#include "File.h"
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "inName outName" << endl;
		return 1;
	}
	
	string inName(argv[1]);
	string outName(argv[2]);
	labFile::FileStringSpliter fss(inName);
	fss.setDefaultDelimiters();
	cout << fss.fillFreqTable() << endl;
	return 0;
}