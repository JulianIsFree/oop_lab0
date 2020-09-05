#pragma once
#include <fstream>
#include <list>
#include <string>

namespace labFile 
{
	class File
	{
	protected:
		std::string fileName;
	public:
		File();
		File(std::string fileName);
		void setFileName(std::string fileName);
	};

	class FileReader : File
	{
	private:
		std::list<std::string> lines;
	public:
		FileReader();
		FileReader(std::string fileName);
		std::list<std::string> getText();
		void readFile();
	};

	class FileWriter : File
	{
	public:
		FileWriter();
		FileWriter(std::string fileName);
	};
}
