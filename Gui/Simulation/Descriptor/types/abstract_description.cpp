#include "abstract_description.h"

AbstractDescription::AbstractDescription() {}
AbstractDescription::AbstractDescription(const std::string& name) :
    name (name) {}
AbstractDescription::AbstractDescription(const char* name) :
    name (name) {}
AbstractDescription::~AbstractDescription() {}
const std::string AbstractDescription::getName () const {
    return name;
}
/*
void AbstractDescription::setName (const std::string& name) {
    this->name = name;
}
*/

