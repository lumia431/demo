#include <iostream>
#include <optional>
#include <string>

// convert string to int if possible:
std::optional<int> asInt(const std::string& s)
{
	try
	{
		return std::stoi(s);
	}
	catch (...)
	{
		return std::nullopt;
	}
}
int main()
{
	for (auto s : { "42", " 077", "hello", "0x33" })
	{
		// convert s to int and use the result if possible:
		std::optional<int> oi = asInt(s);
		if (oi) {
			std::cout << "convert '" << s << "' to int: " << *oi << "\n";
		}
		else {
			std::cout << "can't convert '" << s << "' to int\n";
		}
	}
}