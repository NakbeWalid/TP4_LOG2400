#include "manager.h"
#include "point.h"
#include "nuage.h"

Manager::Manager(std::vector<IElement*>& elems)
    : elements_(elems)
{
}

std::vector<IElement*>& Manager::getElements()
{
    return elements_;
}

PointMD* Manager::getPoint(int id) const
{
    for (auto e : elements_)
    {
        if (auto p = dynamic_cast<PointMD*>(e))
        {
            if (p->getId() == id)
                return p;
        }
    }
    return nullptr;
}

IElement* Manager::getElement(int id) const
{
    for (auto e : elements_)
    {
        if (auto p = dynamic_cast<PointMD*>(e))
        {
            if (p->getId() == id)
                return e;
        }
        else if (auto n = dynamic_cast<Nuage*>(e))
        {
            if (n->getId() == id)
                return e;
        }
    }
    return nullptr;
}