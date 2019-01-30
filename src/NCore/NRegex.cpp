// © 2019 NIREX ALL RIGHTS RESERVED

#include "NRegex.h"
#include "NRegexFlags.h";

namespace NLib
{
	NRegex::NRegex(void)
		: prefixes("")
		, source("")
		, suffixes("")
		, pattern("")
		, modifiers(0)
	{}

	NRegex& NRegex::Add(const std::string& value)
	{
		source = source + value;
		pattern = prefixes + source + suffixes;
		return (*this);
	}

	NRegex& NRegex::StartOfLine(const bool enable)
	{
		prefixes = enable ? "^" : "";
		return Add("");
	}

	NRegex& NRegex::StartOfLine(void)
	{
		return StartOfLine(true);
	}

	NRegex& NRegex::EndOfLine(const bool enable)
	{
		suffixes = enable ? "$" : "";
		return Add("");
	}

	NRegex& NRegex::EndOfLine(void)
	{
		return EndOfLine(true);
	}

	NRegex& NRegex::Then(const std::string& value)
	{
		return Add("(?:" + value + ")");
	}

	NRegex& NRegex::Find(const std::string& value)
	{
		return Then(value);
	}

	NRegex& NRegex::Maybe(const std::string& value)
	{
		return Add("(?:" + value + ")?");
	}

	NRegex& NRegex::Anything(void)
	{
		return Add("(?:.*)");
	}

	NRegex& NRegex::AnythingBut(const std::string& value)
	{
		return Add("(?:[^" + value + "]*)");
	}

	NRegex& NRegex::Something(void)
	{
		return Add("(?:.+)");
	}

	NRegex& NRegex::SomethingBut(const std::string& value)
	{
		return Add("(?:[^" + value + "]+)");
	}

	std::string NRegex::Replace(const std::string& source, const std::string& value)
	{
		return std::regex_replace(source, std::regex(pattern, CheckFlags()), value);
	}

	NRegex& NRegex::Linebreak(void)
	{
		return Add("(?:(?:\\n)|(?:\\r\\n))");
	}

	NRegex& NRegex::Br(void)
	{
		return Linebreak();
	}

	NRegex& NRegex::Tab(void)
	{
		return Add("\\t");
	}

	NRegex& NRegex::Word(void)
	{
		return Add("\\w+");
	}

	NRegex& NRegex::AnyOf(const std::string& value)
	{
		return Add("[" + value + "]");
	}

	NRegex& NRegex::Any(const std::string& value)
	{
		return AnyOf(value);
	}

	NRegex& NRegex::Range(const std::vector<std::pair<std::string, std::string>>& args)
	{
		std::stringstream value;
		value << "[";

		for (const auto& item : args)
		{
			const std::string from = item.first;
			const std::string to = item.second;

			value << from << "-" << to;
		}

		value << "]";

		return Add(value.str());
	}

	NRegex& NRegex::Range(const std::string& a, const std::string& b)
	{
		return Range({ { a, b } });
	}

	NRegex& NRegex::AddModifier(const char modifier)
	{
		switch (modifier)
		{
		case 'i':
			modifiers |= RXF_CASEINSENSITIVE;
			break;
		case 'm':
			modifiers |= RXF_MULTILINE;
			break;
		case 'g':
			modifiers |= RXF_GLOBAL;
			break;
		default:
			break;
		}

		return (*this);
	}

	NRegex& NRegex::RemoveModifier(const char modifier)
	{
		switch (modifier)
		{
		case 'i':
			modifiers ^= RXF_CASEINSENSITIVE;
			break;
		case 'm':
			modifiers ^= RXF_MULTILINE;
			break;
		case 'g':
			modifiers ^= RXF_GLOBAL;
			break;
		default:
			break;
		}

		return (*this);
	}

	NRegex& NRegex::WithAnyCase(const bool enable)
	{
		if (enable)
		{
			AddModifier('i');
		}
		else
		{
			RemoveModifier('i');
		}

		return (*this);
	}

	NRegex& NRegex::WithAnyCase(void)
	{
		return WithAnyCase(true);
	}

	NRegex& NRegex::SearchOneLine(const bool enable)
	{
		if (enable)
		{
			RemoveModifier('m');
		}
		else
		{
			AddModifier('m');
		}

		return (*this);
	}

	NRegex& NRegex::SearchOneLine(void)
	{
		return SearchOneLine(true);
	}

	NRegex& NRegex::SearchGlobal(const bool enable)
	{
		if (enable)
		{
			AddModifier('g');
		}
		else
		{
			RemoveModifier('g');
		}

		return (*this);
	}

	NRegex& NRegex::SearchGlobal(void)
	{
		return SearchGlobal(true);
	}

	NRegex& NRegex::Multiple(const std::string& value)
	{
		if (value.length() > 0 && value.at(0) != '*' && value.at(0) != '+')
		{
			Add("+");
		}

		return Add(value);
	}

	NRegex& NRegex::Alt(const std::string& value)
	{
		if (prefixes.find("(") == std::string::npos)
		{
			prefixes += "(";
		}

		if (suffixes.find(")") == std::string::npos)
		{
			suffixes = ")" + suffixes;
		}

		Add(")|(");

		return Then(value);
	}

	bool NRegex::Test(const std::string& value)
	{
		const std::string to_test = (modifiers& RXF_MULTILINE) ? value : ReduceLines(value);

		if (modifiers& RXF_GLOBAL)
		{
			return std::regex_search(to_test, std::regex(pattern, CheckFlags()));
		}
		else
		{
			return std::regex_match(to_test, std::regex(pattern, CheckFlags()));
		}
	}

	std::regex::flag_type NRegex::CheckFlags(void) const
	{
		return (modifiers& RXF_CASEINSENSITIVE) ? std::regex::icase : static_cast<std::regex::flag_type>(0);
	}

	std::string NRegex::ReduceLines(const std::string& value) const
	{
		const std::size_t pos = value.find("\n");

		if (pos == std::string::npos)
		{
			return value;
		}

		return value.substr(0, pos);
	}

	std::ostream& operator<<(std::ostream& strm, NRegex& v)
	{
		return strm << v.pattern;
	}
}
