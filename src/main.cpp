#include <iostream>
#include "AnyItem.h"

using namespace any;

template <typename T>
void test(AnyItem item) {
	std::cout << "Hello World " << item.asType<T>() << " " << item << std::endl;
}

int main(int argc, char** argv) {
	AnyItem v = ValueItem<char>('a');
	ValueItem<int> item(3);
	item = 4;

	ValueItem<int*> item2(new int(34));

	test<double>(item);
	test<std::string>(ValueItem<std::string>("abc"));
	test<int>(item2);

	int* s = item2.asType<int*>();

	std::cout << *item2.asType<int*>() << " " << item2 << std::endl;

	//std::cout << item2["this"]["is"]["a"].asType<std::string>("test") << std::endl;

	AnyItem item3;
	item3["again"] = 1;
	item3["again"] = std::string("test");
	item3["again2"] = std::string("what");
	item3["again"] = std::string("test2");
	item3["test"]["again"] = std::string("bed");
	item3["test"]["again"] = 3.14;
	item3["blah"] = new int(23);

	item3["AnyType"] = AnyItem();
	item3["AnyType"]["that"] = 7;
	item3["AnyType"]["this"] = 24;

	AnyItem item5 = item3;

	std::vector<std::string> keys = item3.getKeys();
	for (int f = 0; f < keys.size(); f++) {
		std::cout << "\t" << keys[f] << ": " << item3[keys[f]] << std::endl;
	}

	item5["AnyType"]["this"] = 27;

	std::cout << item3 << std::endl;
	std::cout << item5 << std::endl;

	std::cout << item3["AnyType"]["that"] << std::endl;
	std::cout << item3["test"]["again"] << std::endl;

	std::cout << *item3["blah"].asType<int*>() << std::endl;

	return 0;
}
