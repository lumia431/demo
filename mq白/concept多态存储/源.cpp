#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<variant>
using namespace std;

template<typename T>
concept Drawable = requires(T t) {
	t.draw();
};

struct Line {
	constexpr int draw() {
		return 1;
	}
};

struct Rect {
	constexpr int draw() {
		return 2;
	}
};

struct Apple {
	void eat()const {
		cout << "Apple eat" << endl;
	}
};

template<Drawable T>
void process(const T& shape) {
	shape.draw();
}

int main() {
	Line line;
	Apple apple;
	Rect rect;
	//process(apple);
	//process(line);
	using Shape = variant<Line, Rect>;
	vector<Shape>vec;
	vec.emplace_back(line);
	vec.emplace_back(rect);
	//for (auto& elem : vec) {
	//	auto visitor = [](Drawable auto& d) {
	//		d.draw();
	//	};
	//	std::visit(visitor, elem);
	//}
	auto visitor = [](Drawable auto& d) {
		return d.draw();
	};
	//auto visitor = [](Drawable auto& d) {
	//	return d.draw();
	//};
	constexpr int a = visitor(line);
	constexpr int b = visitor(rect);
	//constexpr auto val = visit(visitor, vec.front());
	static_assert(a == 1);
	static_assert(b == 2);
	system("pause");
	return 0;
}