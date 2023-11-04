#pragma once
#include <string>

namespace nc {
	class StringUtils {
	public:
		std::string ToUpper(std::string str);
		std::string ToLower(std::string str);
		bool IsEqualIgnoreCase(std::string str1, std::string str2);
		std::string CreateUnique(std::string str);
	private:
		//for the CreateUnique function
		uint32_t m_counter = -1;
	};
}