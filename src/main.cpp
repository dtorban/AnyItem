#include <iostream>
#include "impl/ValueItem.h"

using namespace any;

void test(AnyItem item) {
	std::cout << "Hello World " << item.asType<int>() << std::endl;
}

int main(int argc, char** argv) {
	//AnyItem item3;
	//ValueItem<int> item2(4);
	//AnyItem item(ValueItem<int>(3));
	AnyItem item = ValueItem<int>(3);

	test(ValueItem<int>(4));

	/*AnyItem item;
	ValueItem<int> item2(3);
	item = item2;*/

	//ValueItem<int> item(3);
	//item = item2;

	//item.getValue();
	//std::cout << "Hello World." << std::endl;
	//std::cout << item.asType<int>() << std::endl;
	//std::cout <<" " << item2.asType<int>() << std::endl;
	return 0;
}
