/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef ANYITEMIMPL_H_
#define ANYITEMIMPL_H_

#include <string>
#include <iostream>
#include <typeinfo>
#include <vector>

namespace any {

class AnyItem;

class AnyItemImpl {
public:
	virtual ~AnyItemImpl() {}

	virtual void* createItem() const = 0;
	virtual void copyItem(void* state, void* newState) const = 0;
	virtual void deleteItem(void* state) const = 0;
	virtual void destroyState(void* state) const {}
	virtual AnyItem& getItem(const std::string& key, void* state) const = 0;
	virtual const AnyItem& getItemConst(const std::string& key, const void* state) const = 0;
	virtual std::vector<std::string> getKeys(const void* state) const = 0;
	virtual void remove(const std::string& key, void* state) const = 0;
	virtual void* getValue(void* state) const = 0;
	virtual void write(std::ostream& out, const void* state) const = 0;
	virtual void read(std::istream& in, void* state) const = 0;
	virtual const std::type_info& getType() const = 0;
	virtual void push(const AnyItem& item, void* state) const = 0;
	virtual AnyItem& getItem(int index, void* state) const = 0;
	virtual const AnyItem& getItemConst(int index, const void* state) const = 0;
	virtual void remove(int index, void* state) const = 0;
	virtual int size(void* state) const = 0;
	virtual bool isValue() const { return false; }
};

} /* namespace any */

#endif /* ANYITEMIMPL_H_ */
