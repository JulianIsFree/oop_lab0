#include <string>
#include <map>
#include <list>

/*
template < class Key,                                     // map::key_type
		   class T,                                       // map::mapped_type
		   class Compare = less<Key>,                     // map::key_compare
		   class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
		   > class map
*/

namespace labStatCollector
{
	class StatCollector
	{
		std::list<std::string> text;
	private:
		StatCollector(std::list<std::string> text);
		StatCollector();
		~StatCollector();

	public:
		void setParsingText(std::list<std::string> text);
		void collectStat();
		std::map<std::string, int> getParsedData();
	};
}
