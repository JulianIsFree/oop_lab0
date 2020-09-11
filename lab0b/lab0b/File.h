#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <string>

namespace labFile 
{
	struct DelimsLocale : std::ctype<char>
	{
		DelimsLocale(std::string const &delims) : std::ctype<char>(get_table(delims)) {}

		static std::ctype_base::mask const* get_table(std::string const &delims) 
		{
			static std::vector<std::ctype_base::mask> delimiters(table_size, std::ctype_base::mask()); 

			for (unsigned char ch : delims)
			{
				delimiters[ch] = std::ctype_base::space;
			}
				
			return &delimiters[0];
		}
	};

	class FileStringSpliter : public std::ifstream
	{
	private:
		std::map<std::string, size_t> freqTable;
		std::list<std::pair<std::string, int>> freqList;
		std::string delimiters;
	public:
		FileStringSpliter() : std::ifstream() {};
		FileStringSpliter(std::string &fileName) : std::ifstream(fileName) {};
		void setDelimiters(std::string &delims);
		void setDefaultDelimiters();
		void printFreqList();
		bool fillAndSortFreqList();
		bool fillFreqTable();
		bool cmp(std::pair<std::string, int> first, std::pair<std::string, int> second);

	};
}
