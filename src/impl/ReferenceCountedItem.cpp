/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <impl/ReferenceCountedItem.h>

namespace any {

ReferenceCountedItem::ReferenceCountedItem(AnyItem item) : referenceCountedImpl(getItemImpl(item)) {
	impl = &referenceCountedImpl;
	state = impl->createItem();
	ReferenceCountedItemImpl::CountedItem& counted = *static_cast<ReferenceCountedItemImpl::CountedItem*>(state);
	void* copiedState = getItemImpl(item)->createItem();
	getItemImpl(item)->copyItem(getItemState(item), copiedState);
	counted.state = copiedState;
	counted.count = new long(1);
}

ReferenceCountedItem::~ReferenceCountedItem() {
}

void* ReferenceCountedItemImpl::createItem() const {
	return new CountedItem();
}

void ReferenceCountedItemImpl::copyItem(void* state,
		void* newState) const {
	CountedItem* counted = static_cast<CountedItem*>(state);
	(*counted->count)++;
	*static_cast<CountedItem*>(newState) = *static_cast<CountedItem*>(state);
}

void ReferenceCountedItemImpl::deleteItem(void* state) const {
	CountedItem* counted = static_cast<CountedItem*>(state);
	(*counted->count)--;
	if (*counted->count == 0) {
		impl->destroyState(counted->state);
		impl->deleteItem(counted->state);
		delete counted->count;
	}
	delete (CountedItem*)state;
}

AnyItem& ReferenceCountedItemImpl::getItem(const std::string& key,
		void* state) const {
	CountedItem& counted = *static_cast<CountedItem*>(state);
	return impl->getItem(key, counted.state);
}

const AnyItem& ReferenceCountedItemImpl::getItemConst(
		const std::string& key, const void* state) const {
	const CountedItem& counted = *static_cast<const CountedItem*>(state);
	return impl->getItemConst(key, counted.state);
}

std::vector<std::string> ReferenceCountedItemImpl::getKeys(
		const void* state) const {
	const CountedItem& counted = *static_cast<const CountedItem*>(state);
	return impl->getKeys(counted.state);
}

void* ReferenceCountedItemImpl::getValue(void* state) const {
	CountedItem& counted = *static_cast<CountedItem*>(state);
	return impl->getValue(counted.state);
}

void ReferenceCountedItemImpl::write(std::ostream& out,
		const void* state) const {
	const CountedItem& counted = *static_cast<const CountedItem*>(state);
	impl->write(out, counted.state);
}

void ReferenceCountedItemImpl::read(std::istream& in, void* state) const {
	CountedItem& counted = *static_cast<CountedItem*>(state);
	impl->read(in, counted.state);
}

void ReferenceCountedItemImpl::remove(const std::string& key,
		void* state) const {
	CountedItem& counted = *static_cast<CountedItem*>(state);
	impl->remove(key, counted.state);
}

const std::type_info& ReferenceCountedItemImpl::getType() const {
	return impl->getType();
}

void ReferenceCountedItemImpl::push(const AnyItem& item,
		void* state) const {
	CountedItem& counted = *static_cast<CountedItem*>(state);
	impl->push(item, counted.state);
}

AnyItem& ReferenceCountedItemImpl::getItem(int index, void* state) const {
	CountedItem& counted = *static_cast<CountedItem*>(state);
	return impl->getItem(index, counted.state);
}

const AnyItem& ReferenceCountedItemImpl::getItemConst(int index,
		const void* state) const {
	const CountedItem& counted = *static_cast<const CountedItem*>(state);
	return impl->getItemConst(index, counted.state);
}

void ReferenceCountedItemImpl::remove(int index, void* state) const {
	const CountedItem& counted = *static_cast<const CountedItem*>(state);
	return impl->remove(index, counted.state);
}

int ReferenceCountedItemImpl::size(void* state) const {
	const CountedItem& counted = *static_cast<const CountedItem*>(state);
	return impl->size(counted.state);
}



} /* namespace any */

