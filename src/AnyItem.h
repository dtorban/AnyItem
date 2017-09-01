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
	AnyItem(AnyItemImpl* impl);
	AnyItem(const AnyItem& item);
	virtual ~AnyItem();

	template <typename T>
	T asType(T defaultValue = T()) const;
	void remove(const std::string& key);
	std::vector<std::string> getKeys() const;

	AnyItem& operator[](const std::string& key);
	const AnyItem& operator[](const std::string& key) const;
	template <typename T>
	void operator=(const T& item);
	friend std::ostream& operator<<(std::ostream& stream, const AnyItem& item);
	friend std::istream& operator>> (std::istream& stream, AnyItem& item);

	// Array methods
	AnyItem& toArray();
	template <typename T>
	AnyItem& push(const T& val);
	void remove(int index);
	AnyItem& operator[](int index);
	int size();

	static AnyItem& blank();

private:
	void copy(const AnyItem& item);
	void* getValue() const;
	void pushValue(const AnyItem& item);

protected:
	void* state;
	AnyItemImpl* impl;
	bool readOnly;

private:
	long sanityCheck;
	static long getSanityCheckValue() { return 103; }

	template<typename T>
	struct AnyItemAsTypeHelper {
		static T asType(const any::AnyItem& anyItem, T defaultValue) {
			std::stringstream ss;
			ss << anyItem;
			std::istringstream is(ss.str().c_str());

			T val;
			is >> val;
			if (!is) {
				return defaultValue;
			}
			else {
				return val;
			}
		}
	};

	template<typename T>
	struct AnyItemAsTypeHelper<T*> : AnyItemAsTypeHelper<T> {
		static T* asType(const any::AnyItem& anyItem, T* defaultValue) {
			return *(T**)anyItem.getValue();
		}
	};
};

} /* namespace any */

template<typename T>
inline T any::AnyItem::asType(T defaultValue) const {
	return any::AnyItem::AnyItemAsTypeHelper<T>::asType(*this, defaultValue);
}

#include "AnyItemImpl.h"
#include "impl/ValueItem.h"

namespace any {

template <typename T>
struct ValueItemConverter {
	static any::ValueItem<T> getAnyItem(const T &val) {
		return any::ValueItem<T>(val);
	}
};

template <>
struct ValueItemConverter<char*> {
	static any::AnyItem getAnyItem(const char* val) {
		return any::ValueItem<std::string>(std::string(val));
	}
};

template <>
struct ValueItemConverter<any::AnyItem> {
	static any::AnyItem getAnyItem(const any::AnyItem &val) {
		return val;
	}
};

}

template <typename T>
inline void any::AnyItem::operator=(const T& val) {
	AnyItem item = any::ValueItemConverter<T>::getAnyItem(val);
	copy(item);
}

template <typename T>
any::AnyItem& any::AnyItem::push(const T& val) {
	AnyItem item = any::ValueItemConverter<T>::getAnyItem(val);
	pushValue(item);
	return *this;
}

#endif /* ANYITEM_H_ */
