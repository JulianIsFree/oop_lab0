#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <algorithm>


namespace labFile 
{	
	inline bool cmp(std::pair<std::string, size_t> first, std::pair<std::string, size_t> second)
	{
		return first.second > second.second;
	}

	struct DelimsLocale : std::ctype<char>
	{
		DelimsLocale(std::string const &delims) : std::ctype<char>(get_table(delims)) {}

		static std::ctype_base::mask const* get_table(std::string const &delims) 
		{
			static std::vector<std::ctype_base::mask> delimiters(table_size, std::ctype_base::mask()); 
			for (unsigned char ch : delims)
				delimiters[ch] = std::ctype_base::space;
				
			return &delimiters[0];
		}
	};

	class FileStringSpliter : public std::ifstream
	{
	private:
		std::map<std::string, size_t> freqTable;
		std::list<std::pair<std::string, size_t>> freqList;
		std::string delimiters;
		size_t wordCounter;
	public:
		FileStringSpliter() : std::ifstream() { wordCounter = 0; };
		FileStringSpliter(const std::string & fileName) : std::ifstream(fileName) { wordCounter = 0; };
		~FileStringSpliter();
		void setDelimiters(const std::string & delims);
		void setDefaultDelimiters();
		bool fillAndSortFreqList();
		bool fillFreqTable();
		bool removeDelim(const char delim);
		const std::list<std::pair<std::string, size_t>> &getList();
		size_t getWordCounter();
	};

	class FileWriter : public std::ofstream
	{
	private:
		std::list<std::pair<std::string, size_t>> text;
		size_t wordCounter;
	public:
		FileWriter() : std::ofstream() { wordCounter = 0; };
		FileWriter(const std::string & fileName) : std::ofstream(fileName) { wordCounter = 0; };
		~FileWriter();
		void setText(const std::list<std::pair<std::string, size_t>> &text);
		void setText(FileStringSpliter & fss);
		bool writeCSV();
		size_t getWordCounter();
	};
}
