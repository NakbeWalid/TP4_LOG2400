#include "manager.h"

Manager::Manager(std::vector<IElement *> &elems)
    : elements_(elems)
{
}

IElement *Manager::getElement(int id) const
{
    for (auto e : elements_)
    {
        auto pts = e->getPoints();
        for (auto p : pts)
            if (p->getId() == id)
                return e;
    }
    return nullptr;
}

PointMD *Manager::getPoint(int id) const
{
    for (auto e : elements_)
    {
        auto pts = e->getPoints();
        for (auto p : pts)
            if (p->getId() == id)
                return p;
    }
    return nullptr;
}

Nuage* Manager::getNuage(int id) const
{
    for (auto e : elements_)
    {
        Nuage* n = dynamic_cast<Nuage*>(e);
        if (n && n->getId() == id)
            return n;
    }
    return nullptr;
}


std::vector<IElement *> &Manager::getElements()
{
    return elements_;
}