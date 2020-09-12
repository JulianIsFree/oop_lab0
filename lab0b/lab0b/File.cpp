#include "File.h"

labFile::FileStringSpliter::~FileStringSpliter()
{
}

void labFile::FileStringSpliter::setDelimiters(const std::string & delims)
{
	delimiters = delims;
}

void labFile::FileStringSpliter::setDefaultDelimiters()
{
	delimiters = "";
	for (int i = 0; i < 256; ++i)
		if(!isdigit(i) && !isalpha(i))
			delimiters.push_back(i);
}

bool labFile::FileStringSpliter::fillAndSortFreqList()
{
	if (freqTable.empty())
		return false;
	freqList.clear();
	wordCounter = 0;
	for (auto iter = freqTable.begin(); iter != freqTable.end(); ++iter)
	{
		freqList.push_back(std::pair<std::string, size_t>(iter->first, iter->second));
		wordCounter += iter->second;
	}
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
			freqTable[word]++;
		iss.clear();
	}
	
	return true;
}

bool labFile::FileStringSpliter::removeDelim(const char delim)
{
	size_t index = delimiters.find(delim);
	if (index < 0)
		return false;
	delimiters.erase(index);
	return true;
}

const std::list<std::pair<std::string, size_t>>& labFile::FileStringSpliter::getList()
{
	return freqList;
}

size_t labFile::FileStringSpliter::getWordCounter()
{
	return wordCounter;
}

labFile::FileWriter::~FileWriter()
{

}

void labFile::FileWriter::setText(const std::list<std::pair<std::string, size_t>> &text)
{
	this->text.clear();
	this->text = text;
	
	wordCounter = 0;
	for (auto iter = text.begin(); iter != text.end(); ++iter)
		wordCounter += iter->second;
}

void labFile::FileWriter::setText(FileStringSpliter & fss)
{
	this->text.clear();
	this->text = fss.getList();
	this->wordCounter = fss.getWordCounter();
}

bool labFile::FileWriter::writeCSV()
{
	if(!this->is_open())
		return false;

	for (auto iter = text.begin(); iter != text.end(); ++iter)
		*this << iter->first << "," << iter->second << "," << static_cast<double>(iter->second * 100) / wordCounter << "%" <<std::endl;

	return true;
}

size_t labFile::FileWriter::getWordCounter()
{
	return wordCounter;
}
