// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_REGEX_H_
#define _N_REGEX_H_

#include "NDefines.h"
#include "NObject.h"

#include <regex>
#include <sstream>

namespace NLib
{
	class NAPI NRegex final : public NObject
	{
	public:
		NRegex(void);
		NRegex& operator=(const NRegex& ve) = default;
		~NRegex(void) = default;

		NRegex& Add(const std::string& value);

		NRegex& StartOfLine(const bool enable);
		NRegex& StartOfLine(void);

		NRegex& EndOfLine(const bool enable);
		NRegex& EndOfLine(void);

		NRegex& Then(const std::string& value);
		NRegex& Find(const std::string& value);
		NRegex& Maybe(const std::string& value);
		NRegex& Anything(void);
		NRegex& AnythingBut(const std::string& value);
		NRegex& Something(void);
		NRegex& SomethingBut(const std::string& value);

		std::string Replace(const std::string& source, const std::string& value);

		NRegex& Linebreak(void);
		NRegex& Br(void);
		NRegex& Tab(void);
		NRegex& Word(void);

		NRegex& AnyOf(const std::string& value);
		NRegex& Any(const std::string& value);

		NRegex& Range(const std::vector<std::pair<std::string, std::string>>& args);
		NRegex& Range(const std::string& a, const std::string& b);

		NRegex& AddModifier(const char modifier);
		NRegex& RemoveModifier(const char modifier);

		NRegex& WithAnyCase(const bool enable);
		NRegex& WithAnyCase(void);

		NRegex& SearchOneLine(const bool enable);
		NRegex& SearchOneLine(void);

		NRegex& SearchGlobal(const bool enable);
		NRegex& SearchGlobal(void);

		NRegex& Multiple(const std::string& value);
		NRegex& Alt(const std::string& value);

		bool Test(const std::string& value);

	private:
		std::string prefixes;
		std::string source;
		std::string suffixes;
		std::string pattern;
		unsigned int modifiers;

		std::regex::flag_type check_flags(void) const;
		std::string reduce_lines(const std::string& value) const;
		friend std::ostream& operator<<(std::ostream &strm, NRegex &v);
	};
}
#endif // !_N_REGEX_H_