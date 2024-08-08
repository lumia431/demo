#pragma once
#include <string>

namespace Minidump
{
	static const std::string CRASH_DUMP_FILENAME = "crashdump.mdmp";
	void startMonitering(const std::string& binDir);
}
