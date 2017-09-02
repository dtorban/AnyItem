#include <iostream>
#include "AnyItem.h"
#include "impl/BlankItem.h"

using namespace any;

template <typename T>
void test(const AnyItem& item) {
	std::cout << "Hello World " << item.asType<T>() << " " << item << std::endl;
}

void print(AnyItem item) {
	std::cout << item << std::endl;
}

void printSomething(const AnyItem& item) {
	std::cout << "Const test: " << item["ThisTest"]["Another"] << " " << item["inc"] << " " << item[2]<< " " << item[20] << std::endl;
}

int main(int argc, char** argv) {
	AnyItem v = ValueItem<char>('a');
	ValueItem<int> item(3);
	item = 4;

	ValueItem<int*> item2(new int(34));

	test<double>(item);
	test<std::string>(ValueItem<std::string>("abc"));
	test<int>(item2);

	int* s = item2.asPtr<int*>();

	std::cout << *item2.asPtr<int*>() << " " << item2 << std::endl;

	//std::cout << item2["this"]["is"]["a"].asType<std::string>("test") << std::endl;

	AnyItem item3;
	item3["again"] = 1;
	item3["again"] = std::string("test");
	item3["again2"] = std::string("what");
	item3["again"] = std::string("test2");
	item3["test"]["again"] = std::string("bed");
	item3["test"]["again"] = 3.14;
	item3["blah"] = new int(23);
	item3["blah2"] = (int*)(NULL);
	item3["items"].push(2).push(5).push(std::string("again"));
	item3["items"].push(AnyItem())[3].push(67);
	item3["items"][3].push(67);


	std::cout << *item3["blah"].asPtr<int*>() << std::endl;
	*item3["blah"].asPtr<int*>() = 5;
	std::cout << *item3["blah"].asPtr<int*>() << std::endl;

	item3["AnyType"]["that"] = 7;
	item3["AnyType"]["this"] = 24;

	BlankItem::instance()["test"] = 5;

	std::cout << BlankItem::instance() << std::endl;

	item3["inc"].toArray();
	item3["inc"][0] = 3;
	item3["inc"][1] = 4;
	item3["inc"][2] = AnyItem();
	item3["inc"][10] = 5;
	item3["inc"][7] = std::string("hello");

	printSomething(item3);

	AnyItem item5 = item3;

	item5.remove("blah2");

	item5["items"].remove(2);
	item5["items"][2][1] = 55;

	std::vector<std::string> keys = item3.getKeys();
	for (int f = 0; f < keys.size(); f++) {
		std::cout << "\t" << keys[f] << ": " << item3[keys[f]] << std::endl;
	}

	item5["inc"][8]["test"] = 23;
	//item5["inc"][5] = 1;

	item5["AnyType"]["this"] = 27;

	print(item3);
	print(item5);

	std::cout << item3["AnyType"]["that"] << std::endl;
	std::cout << item3["test"]["again"] << std::endl;

	std::cout << *item3["blah"].asPtr<int*>() << std::endl;

	delete item3["blah"].asPtr<int*>();

	return 0;
}
