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
	virtual AnyItem& getItem(const std::string& key, void* state) const = 0;
	virtual std::vector<std::string> getKeys(const void* state) const = 0;
	virtual void remove(const std::string& key, void* state) const = 0;
	virtual void* getValue(void* state) const = 0;
	virtual void write(std::ostream& out, const void* state) const = 0;
	virtual void read(std::istream& in, void* state) const = 0;
	virtual const std::type_info& getType() const = 0;
};

} /* namespace any */

#endif /* ANYITEMIMPL_H_ */
