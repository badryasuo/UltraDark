#ifndef DARK_AI
#define DARK_AI
#include <list>
namespace dark
{
	class ai
	{
	public:
		ai();
		// remember a list of integers
		void rem(std::list<int> x, const char* tag);
		std::list<int>what(const char* tag);
	private:
		const char** memory;
	};
}
#endif