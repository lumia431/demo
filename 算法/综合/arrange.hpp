#pragma once
#include <vector>
#include <algorithm>
using namespace std;

struct Program
{
	int start;
	int end;
	Program(int st, int en) :start(st), end(en) {};
};

std::vector<Program> Arrange(std::vector<Program> &progs, int start, int end)
{
	std::vector< Program> res;
	std::sort(progs.begin(), progs.end(), [](const Program& p1, const Program& p2) {return p1.end < p2.end; });
	int cur = start;
	for (int i = 0; i < progs.size(); ++i)
	{
		if (progs[i].end > end)
		{
			return res;
		}
		if (progs[i].start >= cur)
		{
			res.emplace_back(progs[i]);
			cur = progs[i].end;
		}
	}
	return res;
}
