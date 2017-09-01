/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <impl/BlankItem.h>

namespace any {

AnyItem& BlankItem::instance() {
	static BlankItem item;
	return item;
}

BlankItem::BlankItem() {
	impl = BlankItemImpl::instance();
	state = NULL;
	readOnly = true;
}

BlankItem::~BlankItem() {
}


void* BlankItemImpl::createItem() const {
	return NULL;
}

void BlankItemImpl::copyItem(void* state, void* newState) const {
}

void BlankItemImpl::deleteItem(void* state) const {
}

AnyItem& BlankItemImpl::getItem(const std::string& key,
		void* state) const {
	return BlankItem::instance();
}

const AnyItem& BlankItemImpl::getItemConst(const std::string& key,
		const void* state) const {
	return BlankItem::instance();
}

std::vector<std::string> BlankItemImpl::getKeys(const void* state) const {
	return std::vector<std::string>();
}

void* BlankItemImpl::getValue(void* state) const {
	return NULL;
}

void BlankItemImpl::write(std::ostream& out, const void* state) const {
}

void BlankItemImpl::read(std::istream& in, void* state) const {
}

void BlankItemImpl::remove(const std::string& key, void* state) const {
}

const std::type_info& BlankItemImpl::getType() const {
	static const std::type_info& type = typeid(BlankItem);
	return type;
}

AnyItemImpl* BlankItemImpl::instance() {
	static BlankItemImpl impl;
	return &impl;
}

void BlankItemImpl::push(const AnyItem& item, void* state) const {
}

AnyItem& BlankItemImpl::getItem(int index, void* state) const {
	return BlankItem::instance();
}

const AnyItem& BlankItemImpl::getItemConst(int index, const void* state) const {
	return BlankItem::instance();
}

void BlankItemImpl::remove(int index, void* state) const {
}

int BlankItemImpl::size(void* state) const {
	return 0;
}

} /* namespace IVGFX */

