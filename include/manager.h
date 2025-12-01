#pragma once
#include <vector>
#include "IElement.h"

class PointMD;
class Nuage;

class Manager
{
public:
    
    explicit Manager(std::vector<IElement*>& elems);

    std::vector<IElement*>& getElements();

    PointMD* getPoint(int id) const;
    IElement* getElement(int id) const;

private:
    std::vector<IElement*>& elements_;
};
