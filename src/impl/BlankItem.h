/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef BLANKITEM_H_
#define BLANKITEM_H_

#include "AnyItem.h"

namespace any {

class BlankItemImpl : public AnyItemImpl {
public:
	void* createItem() const;
	void copyItem(void* state, void* newState) const;
	void deleteItem(void* state) const;
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

class BlankItem : public AnyItem {
public:
	virtual ~BlankItem();
	static AnyItem& instance();
private:
	BlankItem();
};

} /* namespace any */

#endif /* BLANKITEM_H_ */
