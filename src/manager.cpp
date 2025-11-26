#include "manager.h"

Manager::Manager(std::vector<IElement *> &elems)
    : elements(elems)
{
}

IElement *Manager::getElement(int id)
{
    for (auto e : elements)
    {
        auto pts = e->getPoints();
        for (auto p : pts)
            if (p->getId() == id)
                return e;
    }
    return nullptr;
}

PointMD *Manager::getPoint(int id)
{
    for (auto e : elements)
    {
        auto pts = e->getPoints();
        for (auto p : pts)
            if (p->getId() == id)
                return p;
    }
    return nullptr;
}

std::vector<IElement *> &Manager::getElements()
{
    return elements;
}