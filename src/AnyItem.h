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
	template <typename T>
	void operator=(const T& item);
	friend std::ostream& operator<<(std::ostream& stream, const AnyItem& item);
	friend std::istream& operator>> (std::istream& stream, AnyItem& item);

private:
	void copy(const AnyItem& item);
	void* getValue() const;

protected:
	void* state;
	AnyItemImpl* impl;

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

template <typename T>
struct ValueItemConverter {
	static any::AnyItem getAnyItem(const T &val) {
		return any::ValueItem<T>(val);
	}
};

template <>
struct ValueItemConverter<any::AnyItem> {
	static any::AnyItem getAnyItem(const any::AnyItem &val) {
		return val;
	}
};

template <typename T>
inline void any::AnyItem::operator=(const T& val) {
	AnyItem item = ValueItemConverter<T>::getAnyItem(val);
	copy(item);
}

#endif /* ANYITEM_H_ */
