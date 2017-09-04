/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef VALUEITEM_H_
#define VALUEITEM_H_

namespace any {

template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

template<typename T>
struct item_delete { static void destroy(T& item) {} };

template<typename T>
struct item_delete<T*> { static void destroy(T* item) { delete item; } };

template <typename T>
class ValueItemImpl : public AnyItemImpl {
public:
	void* createItem() const;
	void copyItem(void* state, void* newState) const;
	void deleteItem(void* state) const;
	void destroyState(void* state) const;
	AnyItem& getItem(const std::string& key, void* state) const;
	const AnyItem& getItemConst(const std::string& key, const void* state) const;
	std::vector<std::string> getKeys(const void* state) const;
	void* getValue(void* state) const;
	void write(std::ostream& out, const void* state) const;
	void read(std::istream& in, void* state) const;
	void remove(const std::string& key, void* state) const;
	const std::type_info& getType() const;
	void push(const AnyItem& item, void* state) const;
	AnyItem& getItem(int index, void* state) const;
	const AnyItem& getItemConst(int index, const void* state) const;
	void remove(int index, void* state) const;
	int size(void* state) const;
	static AnyItemImpl* instance();
};

template <typename T>
class ValueItem : public AnyItem {
public:
	ValueItem(T value) : AnyItem(ValueItemImpl<T>::instance()) {
		impl->copyItem(&value, state);
	}

	virtual ~ValueItem() {
	}

	void operator=(T val) {
		impl->copyItem(&val, state);
	}
};

} /* namespace any */

template<typename T>
inline void* any::ValueItemImpl<T>::createItem() const {
	return new T();
}

template<typename T>
inline void any::ValueItemImpl<T>::copyItem(void* state, void* newState) const {
	T* newVal = (T*)newState;
	*newVal = *(T*)state;
}

template<typename T>
inline void any::ValueItemImpl<T>::deleteItem(void* state) const {
	delete (T*)state;
}

template<typename T>
inline void any::ValueItemImpl<T>::destroyState(void* state) const {
	if (is_pointer<T>::value) {
		item_delete<T>::destroy(*static_cast<T*>(state));
	}
}

template<typename T>
inline any::AnyItem& any::ValueItemImpl<T>::getItem(const std::string& key,
		void* state) const {
	return AnyItem::blank();
}

template<typename T>
inline std::vector<std::string> any::ValueItemImpl<T>::getKeys(
		const void* state) const {
	return std::vector<std::string>();
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
		void* state) const {
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

template<typename T>
void any::ValueItemImpl<T>::remove(const std::string& key, void* state) const {
}

template<typename T>
void any::ValueItemImpl<T>::push(const any::AnyItem& item, void* state) const {
}

template<typename T>
any::AnyItem& any::ValueItemImpl<T>::getItem(int index, void* state) const {
	return AnyItem::blank();
}

template<typename T>
const any::AnyItem& any::ValueItemImpl<T>::getItemConst(int index, const void* state) const {
	return AnyItem::blank();
}

template<typename T>
const any::AnyItem& any::ValueItemImpl<T>::getItemConst(const std::string& key, const void* state) const {
	return AnyItem::blank();
}

template<typename T>
void any::ValueItemImpl<T>::remove(int index, void* state) const {
}

template<typename T>
int any::ValueItemImpl<T>::size(void* state) const {
	return 0;
}


#endif /* VALUEITEM_H_ */
