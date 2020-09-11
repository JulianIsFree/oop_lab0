#include "File.h"

void labFile::FileStringSpliter::setDelimiters(std::string & delims)
{
	delimiters = delims;
}

void labFile::FileStringSpliter::setDefaultDelimiters()
{
	delimiters = "";
	for (int i = 1; i < 256; ++i)
		if(!isdigit(i) && !isalpha(i))
			delimiters.push_back(i);
}

bool labFile::FileStringSpliter::fillAndSortFreqList()
{
}

bool labFile::FileStringSpliter::fillFreqTable()
{
	if (!(this->is_open()))
		return false;
	freqTable.clear();
	std::istringstream iss;
	iss.imbue(std::locale(std::locale(), new DelimsContainer(delimiters)));

	std::string line;
	std::string word;
	while (std::getline(*this, line))
	{
		iss.str(line);
		while (iss >> word)
		{
			auto iter = freqTable.find(word);
			if (iter != freqTable.end())
				freqTable[word]++;
			else
				freqTable[word] = 1;
		}
		iss.clear();
	}
	
	return true;
}

bool labFile::FileStringSpliter::cmp(std::pair<std::string, int> first, std::pair<std::string, int> second)
{
	return first.second < second.second;
}
