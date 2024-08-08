
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<time.h>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//template<typename T>
//struct type_wrapper {
//	using type = T;
//};
//
//template<typename T>
////变量模板
////C++14以后，变量也可以参数化为特定的类型，这称为变量模板。
//type_wrapper<T>type;

template<int s> struct Wow;
struct foo {
	int a, b;
};

//如何根据一个运行期的值调用一个编译器模板函数
template<size_t N>
void fun() {
	//对于不同的N作不同的处理
	cout << N << endl;
}

namespace detail {
	template<class Tuple, class F, std::size_t...ls>
	//对一个序列遍历
	auto tuple_switch(const std::size_t i, Tuple&& t, F&& f, std::index_sequence<ls...>) {
		(void)std::initializer_list<int>{
			//如果i!=ls,那么后面的lambda不会执行
			//利用运行期时if(a&&b)，a为真则后面的b就不会执行，实现了switch的功能
			(i == ls && ((void)f(std::integral_constant<size_t, ls>{}), 0))...
		};
	}
}

template<class Tuple, class F>
inline void tuple_switch(const std::size_t i, Tuple&& t, F&& f) {
	constexpr auto N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
	detail::tuple_switch(i, std::forward<Tuple>(t), std::forward<F>(f), std::make_index_sequence<N>{});
}

template<size_t ...ls>
auto make_tuple_from_sequence(std::index_sequence<ls...>)->decltype(std::make_tuple(ls...)) {
	return std::make_tuple(ls...);
}

template<size_t N>
constexpr auto make_tuple_from_sequence()->decltype(make_tuple_from_sequence(std::make_index_sequence<N>{})) {
	return make_tuple_from_sequence(std::make_index_sequence<N>{});
}

void foo1(int n) {
	//fun<n>();//带来一个问题，无法用一个运行期的值作为编译期的参数，所以如何进行转换呢？
	std::tuple<int, int, int, int, int> tp;//fun有多少switch分支,就写多少个int
	tuple_switch(n, tp, [](auto item) {
		constexpr auto l = decltype(item)::value;
		fun<l>();
	});
}

//void foo2(int n) {
//	auto tp = make_tuple_from_sequence<10>();
//	tuple_switch(n, tp, [](auto item) {
//		constexpr auto l = decltype(item)::value;
//		Wow<l> wow;
//		fun<l>();
//	});
//}

int main() {
	//constexpr auto add_pointer = [](auto t) {
	//	using T = typename decltype(t)::type;
	//	//using add_pointer_t=typename add_pointer<T>::type;
	//	return type<std::add_pointer_t<T>>;//type to value
	//};
	//auto the_int_type = type<int>;//type to value 从编译期到运行期
	//using the_real_int_type = decltype(the_int_type)::type;//value to type 从运行期到编译期
	//constexpr auto intptr = add_pointer(type<int>);
	//static_assert(std::is_same_v<decltype(intptr)::type, int*>);
	srand(time(nullptr));
	int a = rand() % 10;
	cout << "a = " << a << endl;
	foo1(a);
	//auto b = std::forward(foo)(a);
	//(void)std::initializer_list<int>{(a==1&&(void)foo(1)),2};
	system("pause");
	return 0;
}