#include <iostream>
#include <string>

#include "File.h"
#include "StatCollector.h"
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
	labFile::FileReader fin(inName);
	labFile::FileWriter fout(outName);
	
	return 0;
}