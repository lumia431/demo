#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include "arrange.hpp"
#include "hannuota.hpp"
#include "printAllSubsequences.hpp"
#include "printAllPermutations.hpp"
#include "CardGame.hpp"
#include "UseLeastCoins.hpp"
#include "SlideWindow.hpp"
#include "monotonousStack.hpp"
using namespace std;
void testArrange()
{
	vector<Program>v;
	Program p1(5, 7);
	Program p2(6, 7);
	Program p3(6, 8);
	Program p4(7, 8);
	Program p5(7, 11);
	Program p6(9, 11);
	Program p7(10, 13);
	Program p8(11, 12);
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);
	v.push_back(p6);
	v.push_back(p7);
	v.push_back(p8);
	auto res = Arrange(v, 6, 12);
}

void testHannuota()
{
	auto res = Hannuota(4);
}

void testPrintAllSubsequences()
{
	PrintAllSubsequences("abcd");
}

void testPrintAllPermutations()
{
	PrintAllPermutations("abcd");
}

void testCardGame()
{
	vector<int> v{ 1,2,3,4,5,6 };
	//CardGame(v);
}

void testUseLeastCoins()
{
	vector<int> v{ 1,8,8,5,2,5,5,5,7,2,8 };
	auto res = UseLeastCoins(v, 55);
}

void testSlideWindow()
{
	vector<int>v{ 1,3,-1,-3,5,3,6,7 };
	//auto res = maxSlidingWindow(v, 3);
	auto res = dandiaoQueue(v, 3);
}

void testMonotonousStack()
{
	std::vector<int> nums = { 3, 4, 2, 7, 5, 8, 10, 6 };

	auto res = monoStack(nums);

	std::cout << "Next Smaller Elements: ";
	for (auto i : res) {
		std::cout << i.first<<'\t' << i.second<<'\n';
	}
}

int main()
{
	//testArrange();
	//testHannuota();
	//testPrintAllSubsequences();
	//testPrintAllPermutations();
	//testUseLeastCoins();
	//priority_queue<int>q;
	//priority_queue<int,vector<int>,greater<int>>q;
	//testSlideWindow();
	testMonotonousStack();
	system("pause");
	return 0;
}