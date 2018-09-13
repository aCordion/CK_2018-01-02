#include <iostream>

namespace myspace1
{
	void function1(void)
	{
		std::cout << "myspace1의 함수1" << std::endl;
	}
	void function2(void)
	{
		std::cout << "myspace1의 함수2" << std::endl;
	}
}
namespace myspace2
{
	void function1(void)
	{
		std::cout << "myspace2의 함수1" << std::endl;
	}
	void function2(void)
	{
		std::cout << "myspace2의 함수2" << std::endl;
	}
}

using myspace1::function1;
using myspace1::function2;
//using myspace2::function1;
//using myspace2::function2;

int main(void) {
	function1();
	function2();
	myspace2::function1();
	myspace2::function2();
	return 0;
}
