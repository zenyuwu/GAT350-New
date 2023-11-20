#pragma once
#include <string>
#include "Framework/Singleton.h"

namespace nc {
	bool IsEqualIgnoreCase(std::string str1, std::string str2);
	std::string ToUpper(std::string str);
	std::string ToLower(std::string str);
	class StringUtils : public Singleton<StringUtils>{
	public:
		std::string CreateUnique(std::string str);
	private:
		//for the CreateUnique function
		uint32_t m_counter = -1;
	};
}