#include "ai.h"
#ifdef DARK_AI
dark::ai::ai()
{
	memory = (const char**)calloc(1, INT_MAX);
}
void dark::ai::rem(std::list<int> x, const char * tag)
{
	
}

std::list<int> dark::ai::what(const char * tag)
{
	return std::list<int>();
}
#endif