/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef VALUEITEM_H_
#define VALUEITEM_H_

#include "AnyItemImpl.h"

namespace any {

template <typename T>
class ValueItemImpl : public AnyItemImpl {
public:
	void* createItem() const;
	void* copyItem(void* state) const;
	void deleteItem(void* state) const;
	AnyItem getItem(const std::string& key, const void* state) const;
	std::vector<std::string> getKeys(void* state) const;
	void* getValue(void* state) const;
	void write(std::ostream& out, const void* state) const;
	void read(std::istream& in, const void* state) const;
	const std::type_info& getType() const;
	static AnyItemImpl* instance();
};

template <typename T>
class ValueItem : public AnyItem {
public:
	ValueItem(T value) {
		impl = ValueItemImpl<T>::instance();
		state = impl->copyItem(&value);
	}

	virtual ~ValueItem() {
	}
};

} /* namespace any */

template<typename T>
inline void* any::ValueItemImpl<T>::createItem() const {
	return new T();
}

template<typename T>
inline void* any::ValueItemImpl<T>::copyItem(void* state) const {
	T* newVal = (T*)createItem();
	*newVal = *(T*)state;
	return newVal;
}

template<typename T>
inline void any::ValueItemImpl<T>::deleteItem(void* state) const {
	delete (T*)state;
}

template<typename T>
inline any::AnyItem any::ValueItemImpl<T>::getItem(const std::string& key,
		const void* state) const {
}

template<typename T>
inline std::vector<std::string> any::ValueItemImpl<T>::getKeys(
		void* state) const {
	static std::vector<std::string> keys;
	return keys;
}

template<typename T>
inline void* any::ValueItemImpl<T>::getValue(void* state) const {
	return state;
}

template<typename T>
inline void any::ValueItemImpl<T>::write(std::ostream& out,
		const void* state) const {
	out << *(T*)state;
}

template<typename T>
inline void any::ValueItemImpl<T>::read(std::istream& in,
		const void* state) const {
}

template<typename T>
inline const std::type_info& any::ValueItemImpl<T>::getType() const {
	static const std::type_info& type = typeid(T);
	return type;
}

template<typename T>
inline any::AnyItemImpl* any::ValueItemImpl<T>::instance() {
	static ValueItemImpl impl;
	return &impl;
}

#endif /* VALUEITEM_H_ */
