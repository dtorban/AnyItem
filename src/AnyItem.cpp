/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "AnyItem.h"
#include "impl/BlankItem.h"

namespace any {

AnyItem::AnyItem() : state(NULL), impl(BlankItemImpl::instance()) {
	sanityCheck = getSanityCheckValue();
}

AnyItem::AnyItem(const AnyItem& item) : state(NULL), impl(BlankItemImpl::instance()) {
	copy(item);
	sanityCheck = getSanityCheckValue();
}

AnyItem::~AnyItem() {
	if (sanityCheck == getSanityCheckValue()) {
		impl->deleteItem(state);
	}
}

std::vector<AnyItem> AnyItem::asArray() const {
	static std::vector<AnyItem> items;
	return items;
}

void AnyItem::set(const std::string& key, const AnyItem& item) {
	impl->set(key, item, state);
}

void AnyItem::remove(const std::string& key) {
	impl->remove(key, state);
}

std::vector<std::string> AnyItem::getKeys() const {
	return impl->getKeys(state);

	static std::vector<std::string> keys;
	return keys;
}

AnyItem AnyItem::operator [](const std::string& key) const {
	if (impl != NULL && state != NULL) {
		return impl->getItem(key, state);
	}

	return BlankItem::instance();
}

void AnyItem::copy(const AnyItem& item) {
	impl->deleteItem(state);

	impl = item.impl;
	state = impl->copyItem(item.state);
}

void* AnyItem::getValue() const {
	return impl->getValue(state);
}

std::ostream& operator<<(std::ostream& stream, const AnyItem& item) {
	item.impl->write(stream, item.state);
	return stream;
}

std::istream& operator>>(std::istream& stream, AnyItem& item) {
	item.impl->read(stream, item.state);
	return stream;
}

} /* namespace any */

