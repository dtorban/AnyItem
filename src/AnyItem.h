/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef ANYITEM_H_
#define ANYITEM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace any {

class AnyItemImpl;

class AnyItem {
public:
	AnyItem();
	AnyItem(const AnyItem& item);
	virtual ~AnyItem();

	template <typename T>
	T asType(T defaultValue = T()) const;
	std::vector<AnyItem> asArray() const;
	void set(const std::string& key, AnyItem item);
	void remove(const std::string& key);
	std::vector<std::string> getKeys() const;

	AnyItem operator[](const std::string& key) const;
	AnyItem operator=(const AnyItem& item);
	friend std::ostream& operator<<(std::ostream& stream, const AnyItem& item);
	friend std::istream& operator>> (std::istream& stream, AnyItem& item);

private:
	void* getValue() const;

protected:
	void* state;
	AnyItemImpl* impl;

private:
	long sanityCheck;
	static long getSanityCheckValue() { return 103; }

public:
	int id;
};

} /* namespace any */

template<typename T>
inline T any::AnyItem::asType(T defaultValue) const {
	std::stringstream ss;
	ss << *this;
	std::istringstream is(ss.str().c_str());

	T val;
	is >> val;
	if (!is) {
		return defaultValue;
	}
	else {
		return val;
	}

	return *(T*)this->getValue();
}


#endif /* ANYITEM_H_ */
