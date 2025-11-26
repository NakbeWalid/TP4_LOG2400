#include "nuage.h"
#include <iostream>
#include <algorithm>

Nuage::Nuage(int id, char texture)
    : id_(id), texture_(texture)
{
}

int Nuage::getId() const { return id_; }
char Nuage::getTexture() const { return texture_; }

const std::vector<IElement*>& Nuage::getEnfants() const
{
    return enfants_;
}

void Nuage::ajouterPoint(IElement* p)
{
    if (p)
        enfants_.push_back(p);
}

void Nuage::retirerPoint(int id)
{
    enfants_.erase(
        std::remove_if(enfants_.begin(), enfants_.end(),
                       [id](IElement* e)
                       {
                           auto pts = e->getPoints();
                           for (auto p : pts)
                               if (p && p->getId() == id)
                                   return true;
                           return false;
                       }),
        enfants_.end());
}

void Nuage::appliquerTexture(char t)
{
    texture_ = t;
    for (auto e : enfants_)
    {
        auto pts = e->getPoints();
        for (auto p : pts)
            if (p)
                p->addTexture(t);
    }
}

void Nuage::afficher() const
{
    std::cout << "Nuage '" << texture_ << "' contient les points: ";
    auto pts = getPoints();
    for (size_t i = 0; i < pts.size(); ++i)
    {
        std::cout << pts[i]->getId();
        if (i + 1 < pts.size())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

void Nuage::afficherDansGrille(std::vector<std::vector<char>>& grille,
                               bool afficherID) const
{
    for (auto e : enfants_)
        if (e)
            e->afficherDansGrille(grille, afficherID);
}

std::vector<PointMD*> Nuage::getPoints() const
{
    std::vector<PointMD*> out;
    for (auto e : enfants_)
    {
        auto pts = e->getPoints();
        out.insert(out.end(), pts.begin(), pts.end());
    }
    return out;
}
