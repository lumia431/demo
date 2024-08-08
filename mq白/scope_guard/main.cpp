#include<iostream>
#include<tuple>
#include<type_traits>
template<typename F, typename...Args>
    requires requires(F f, Args...args) { std::invoke(f, args...); }
struct scope_guard {
    F f;
    std::tuple<Args...>values;

    template<typename Fn, typename...Ts>
    scope_guard(Fn&& func, Ts&&...args) :f{ std::forward<Fn>(func) }, values{ std::forward<Ts>(args)... } {}
    ~scope_guard() {
        std::apply(f, values);
    }
    scope_guard(const scope_guard&) = delete;
};

template<typename F, typename...Args>//推导指引非常重要
scope_guard(F&&, Args&&...) -> scope_guard<std::decay_t<F>, std::decay_t<Args>...>;

struct X {
    X() { puts("X()"); }

    X(const X&) { puts("X(const X&)"); }

    X(X&&) noexcept { puts("X(X&&)"); }

    ~X() { puts("~X()"); }
};

int main()
{
    {
        auto x = new X{};
        auto guard = scope_guard([&] {
            delete x;
            x = nullptr;
            });
    }
    puts("----------");
    {
        struct Test {
            void operator()(X*& x)
            {
                delete x;
                x = nullptr;
            }
        };

        auto x = new X{};
        Test t;
        auto guard = scope_guard(t, x);
    }
    puts("----------");
    {
        struct Test {
            void f(X*& x)
            {
                delete x;
                x = nullptr;
            }
        };

        auto x = new X{};
        Test t;
        auto guard = scope_guard{ &Test::f, &t, x }; // error
    }
}