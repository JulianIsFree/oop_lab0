#include <iostream>
#include <string>

#include "File.h"
using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Wrong args: not enough file names" << endl;
		return 1;
	}
	
	string inName(argv[1]);
	string outName(argv[2]);

	labFile::FileStringSpliter fss(inName);
	fss.setDefaultDelimiters();
	fss.removeDelim('_');
	cout << "File parsed: " << fss.fillFreqTable() << endl;
	cout << "Words sorted: " << fss.fillAndSortFreqList() << endl;
	
	labFile::FileWriter fw(outName);
	fw.setText(fss);
	cout << "List saved :" << fw.writeCSV() << endl;

	fss.close();
	fw.close();
	return 0;
}