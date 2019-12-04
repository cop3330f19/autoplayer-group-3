#ifndef STRING_HELPER
#define STRING_HELPER

#include <string>
#include <sstream>
#include <vector>

class StringHelper{
	
	public:
	/**************************************************************
	 *                             parse                          *
	 *                                                            *
	 * Passed   : 2 arguments: a string, a character that is the  *
	 *            delimiter                                       *
	 * Purpose  : Split a given string by its delimiter           *
	 * Returns  : String vector                                   *
	 **************************************************************/
	static std::vector<std::string> parse(std::string , char );
	
	
	/**************************************************************
	 *                          toUpper                           *
	 *                                                            *
	 * Passed   : 1 argument: a string                            *
	 * Purpose  : Convert string to uppercase                     *
	 * Returns  : String                                          *
	 **************************************************************/
	static std::string toUpper(const std::string );
	
	/**************************************************************
	 *                             stou                           *
	 *                                                            *
	 * Passed   : 1 argument: a string                            *
	 * Purpose  : Replace all spaces with an underscore           *
	 * Returns  : String                                          *
	 **************************************************************/
	static std::string stou(std::string );
	
	/**************************************************************
	 *                             utos                           *
	 *                                                            *
	 * Passed   : 1 argument: a string                            *
	 * Purpose  : Replace all undderscores with a space           *
	 * Returns  : String                                          *
	 **************************************************************/
	static std::string utos(std::string );
	
	
	/**************************************************************
	 *                          toString                          *
	 *                                                            *
	 * Passed   : 1 argument: any built-in type                   *
	 * Purpose  : Convert a value to a string                     *
	 * Returns  : String                                          *
	 **************************************************************/
	template<typename T>
	static std::string toString(const T& value )		
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

};
#endif