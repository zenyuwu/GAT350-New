#include "StringUtils.h"

namespace nc {
	std::string ToUpper(std::string str) {
		//making a new string for the result so we're not changing stuff while iterating through it
		std::string result = str;
		for (size_t i = 0; i < str.length(); i++) {
			//toupper will take a char and make sure it's uppercase
			result[i] = toupper(str[i]);
		}
		return result;
	}

	std::string ToLower(std::string str) {
		//making a new string for the result so we're not changing stuff while iterating through it
		std::string result = str;
		for (size_t i = 0; i < str.length(); i++) {
			//tolower will take a char and make sure it's lowercase
			result[i] = tolower(str[i]);
		}
		return result;
	}

	bool IsEqualIgnoreCase(std::string str1, std::string str2) {
		//turning both strings to lowercase then comparing them
		return ToLower(str1) == ToLower(str2);
	}

	std::string StringUtils::CreateUnique(std::string str) {
		//incrementing the counter of this class
		m_counter++;
		//returning the string with the counter appended to it
		return str + std::to_string(m_counter);
	}	
}