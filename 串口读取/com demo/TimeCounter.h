#pragma once
#include <cstdint>


class TimeCounter
{
public:
	TimeCounter();
	~TimeCounter();

	void Start();
	uint64_t End();

private:
	uint64_t frequency_;
	uint64_t start_;
	uint64_t end_;
};

