/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <impl/ArrayItemImpl.h>
#include <vector>

namespace any {

void* ArrayItemImpl::createItem() const {
	return new std::vector<AnyItem>();
}

void ArrayItemImpl::copyItem(void* state, void* newState) const {
	*static_cast<std::vector<AnyItem>*>(newState) = *static_cast<std::vector<AnyItem>*>(state);
}

void ArrayItemImpl::deleteItem(void* state) const {
	delete static_cast<std::vector<AnyItem>*>(state);
}

AnyItem& ArrayItemImpl::getItem(const std::string& key,
		void* state) const {
	return AnyItem::blank();
}

std::vector<std::string> ArrayItemImpl::getKeys(const void* state) const {
	static std::vector<std::string> keys;
	return keys;
}

void* ArrayItemImpl::getValue(void* state) const {
	return state;
}

void ArrayItemImpl::write(std::ostream& out, const void* state) const {
	const std::vector<AnyItem>& v = *static_cast<const std::vector<AnyItem>*>(state);
	out << "[";
	for (int f = 0; f < v.size(); f++) {
		if (f != 0) {
			out << ",";
		}
		out << v[f];
	}
	out << "]";
}

void ArrayItemImpl::read(std::istream& in, void* state) const {
}

void ArrayItemImpl::remove(const std::string& key, void* state) const {
}

const std::type_info& ArrayItemImpl::getType() const {
	static const std::type_info& type = typeid(std::vector<AnyItem>);
	return type;
}

void ArrayItemImpl::push(const AnyItem& item, void* state) const {
	std::vector<AnyItem>& v = *static_cast<std::vector<AnyItem>*>(state);
	v.push_back(item);
}

AnyItem& ArrayItemImpl::getItem(int index, void* state) const {
	std::vector<AnyItem>& v = *static_cast<std::vector<AnyItem>*>(state);
	if (index < 0 || index >= v.size()) {
		return AnyItem::blank();
	}

	return v[index];
}

void ArrayItemImpl::remove(int index, void* state) const {
	std::vector<AnyItem>& v = *static_cast<std::vector<AnyItem>*>(state);
	v.erase(v.begin() + index);
}

int ArrayItemImpl::size(void* state) const {
	const std::vector<AnyItem>& v = *static_cast<const std::vector<AnyItem>*>(state);
	return v.size();
}

AnyItemImpl* ArrayItemImpl::instance() {
	static ArrayItemImpl impl;
	return &impl;
}

} /* namespace any */
