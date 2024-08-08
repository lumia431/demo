#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<tuple>
using namespace std;

template<typename...Ts>
void tupleForeach(const tuple<Ts...>& tu) {
	[&] <size_t...I>(index_sequence<I...>) {
		cout << "[";
		(..., (cout << get<I>(tu) << (I == sizeof...(Ts) - 1? "" : ",")));
		cout << "]" << endl;
	}(std::make_index_sequence<sizeof...(Ts)>());
}

void tupleForeach(auto& tu) {
	constexpr auto len = tuple_size_v<remove_reference_t<decltype(tu)>>;
	[&] <size_t...I>(index_sequence<I...>) {
		cout << "[";
		(..., (cout << get<I>(tu) << (I == len - 1 ? "" : ",")));
		cout << "]" << endl;
	}(std::make_index_sequence<len>());
}

void f(int a) {
	cout << a << endl;
}

void f(auto a) {
	cout << a << endl;
}

int main() {
	std::tuple t(1, true, 1.0, "haha");
	tupleForeach(t);
	f(1);
	system("pause");
	return 0;
}