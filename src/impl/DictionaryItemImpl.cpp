/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <impl/DictionaryItemImpl.h>
#include "BlankItem.h"

namespace any {

struct SimpleMap {
	std::map<std::string, AnyItem> map;
};

void* DictionaryItemImpl::createItem() const {
	return new SimpleMap;
}

void DictionaryItemImpl::copyItem(void* state, void* newState) const {
	*static_cast<SimpleMap*>(newState) = *static_cast<SimpleMap*>(state);
}

void DictionaryItemImpl::deleteItem(void* state) const {
	delete static_cast<SimpleMap*>(state);
}

AnyItem& DictionaryItemImpl::getItem(const std::string& key,
		void* state) const {
	std::map<std::string, AnyItem>& dict = static_cast<SimpleMap*>(state)->map;
	std::map<std::string, AnyItem>::iterator it = dict.find(key);
	if (it != dict.end()) {
		return it->second;
	}
	else {
		dict.insert(std::pair<std::string, AnyItem>(key, AnyItem()));
		return dict[key];
	}
}

std::vector<std::string> DictionaryItemImpl::getKeys(const void* state) const {
	const std::map<std::string, AnyItem>& dict = static_cast<const SimpleMap*>(state)->map;
	std::vector<std::string> v;
	for(std::map<std::string, AnyItem>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
		v.push_back(it->first);
	}

	return v;
}

void* DictionaryItemImpl::getValue(void* state) const {
	return state;
}

void DictionaryItemImpl::write(std::ostream& out,
		const void* state) const {

	const std::map<std::string, AnyItem>& dict = static_cast<const SimpleMap*>(state)->map;
	std::vector<std::string> keys = getKeys(state);
	out << "{";
	for (int f = 0; f < keys.size(); f++) {
		if (f != 0) {
			out << ",";
		}
		out <<"\"" << keys[f] << "\":";
		std::map<std::string, AnyItem>::const_iterator it = dict.find(keys[f]);
		out << it->second;
	}
	out << "}";
}

void DictionaryItemImpl::read(std::istream& in, void* state) const {
}

void DictionaryItemImpl::remove(const std::string& key,
		void* state) const {
	std::map<std::string, AnyItem>& dict = static_cast<SimpleMap*>(state)->map;
	dict.erase(key);
}

const std::type_info& DictionaryItemImpl::getType() const {
	static const std::type_info& type = typeid(std::map<std::string, AnyItem>);
	return type;
}

AnyItemImpl* DictionaryItemImpl::instance() {
	static DictionaryItemImpl impl;
	return &impl;
}

void DictionaryItemImpl::push(const AnyItem& item, void* state) const {
}

AnyItem& DictionaryItemImpl::getItem(int index, void* state) const {
	std::vector<std::string> keys = getKeys(state);
	if (index < 0 || index >= keys.size()) {
		return BlankItem::instance();
	}

	return getItem(keys[index], state);
}

const AnyItem& DictionaryItemImpl::getItemConst(int index, const void* state) const {
	std::vector<std::string> keys = getKeys(state);
	if (index < 0 || index >= keys.size()) {
		return BlankItem::instance();
	}

	return getItemConst(keys[index], state);
}

void DictionaryItemImpl::remove(int index, void* state) const {
	std::vector<std::string> keys = getKeys(state);
	if (index < 0 && index >= keys.size()) {
		return;
	}

	return remove(keys[index], state);
}

int DictionaryItemImpl::size(void* state) const {
	return static_cast<const SimpleMap*>(state)->map.size();
}

const AnyItem& DictionaryItemImpl::getItemConst(const std::string& key,
		const void* state) const {
	const std::map<std::string, AnyItem>& dict = static_cast<const SimpleMap*>(state)->map;
	std::map<std::string, AnyItem>::const_iterator it = dict.find(key);
	if (it != dict.end()) {
		return it->second;
	}

	return AnyItem::blank();
}

} /* namespace any */

