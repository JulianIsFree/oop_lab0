#include "File.h"

labFile::FileStringSpliter::~FileStringSpliter()
{
}

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
	if (freqTable.empty())
		return false;
	freqList.clear();

	for (auto iter = freqTable.begin(); iter != freqTable.end(); ++iter)
		freqList.push_back(std::pair<std::string, size_t> (iter->first, iter->second));

	freqList.sort(cmp);

	return true;
}

bool labFile::FileStringSpliter::fillFreqTable()
{
	if (!(this->is_open()))
		return false;
	freqTable.clear();
	std::istringstream iss;
	iss.imbue(std::locale(std::locale(), new DelimsLocale(delimiters)));

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

std::list<std::pair<std::string, size_t>> labFile::FileStringSpliter::getList()
{
	return std::list<std::pair<std::string, size_t>>(freqList);
}

labFile::FileWriter::~FileWriter()
{

}

void labFile::FileWriter::setText(std::list<std::pair<std::string, size_t>> text)
{
	this->text.clear();
	this->text = text;
}

bool labFile::FileWriter::writeText()
{
	if(!this->is_open())
		return false;

	for (auto iter = text.begin(); iter != text.end(); ++iter)
		*this << iter->first << " " << iter->second << std::endl;

	return true;
}
