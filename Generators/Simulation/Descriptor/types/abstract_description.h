#ifndef ABSTRACT_DESCRIPTION_H
#define ABSTRACT_DESCRIPTION_H
#include <string>

class AbstractDescription {
public:
    AbstractDescription();
    AbstractDescription(const std::string& name);
    AbstractDescription(const char* name);
    const std::string getName () const;
    //void setName (const std::string& name);
    virtual ~AbstractDescription();
private:
    std::string name;
};

#endif // ABSTRACT_DESCRIPTION_H
