#include<iostream>
#include<vector>

namespace X {
	inline namespace std {

	}
}

using namespace X;

namespace Y {
	struct Y {};
	void f(Y){}
}

int main() {
	//std::vector v{ 1 };
	::std::vector v{ 1 };
	endl(::std::cout);// µ≤Œ“¿¿µ≤È’“
	f(Y::Y());
}