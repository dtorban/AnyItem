/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "AnyItem.h"
#include "AnyItemImpl.h"

namespace any {

AnyItem::AnyItem() : state(NULL), impl(NULL) {
	sanityCheck = getSanityCheckValue();
}

AnyItem::AnyItem(const AnyItem& item) : state(NULL), impl(NULL) {
	*this = item;
	sanityCheck = getSanityCheckValue();
}

AnyItem::~AnyItem() {
	if (impl != NULL && state != NULL && sanityCheck == getSanityCheckValue()) {
		impl->deleteItem(state);
	}
}

std::vector<AnyItem> AnyItem::asArray() const {
}

void AnyItem::set(const std::string& key, AnyItem item) {
}

void AnyItem::remove(const std::string& key) {
}

std::vector<std::string> AnyItem::getKeys() const {
	if (impl != NULL && state != NULL) {
		return impl->getKeys(state);
	}

	static std::vector<std::string> keys;
	return keys;
}

AnyItem AnyItem::operator [](const std::string& key) const {
}

AnyItem AnyItem::operator =(const AnyItem& item) {
	if (impl != NULL && state != NULL) {
		impl->deleteItem(state);
	}

	impl = item.impl;
	state = impl->copyItem(item.state);
}

void* AnyItem::getValue() const {
	return impl->getValue(state);
}

} /* namespace any */

