#include "nuage.h"
#include "texture_decorator_concret.h"
#include <iostream>
#include <algorithm>

Nuage::Nuage(int id, char texture)
    : id_(id), texture_(texture)
{
}

Nuage::~Nuage()
{
    // Nettoyer les decorators
    for (auto decorator : decorators_)
    {
        if (decorator)
            delete decorator;
    }
    decorators_.clear();
}

int Nuage::getId() const { return id_; }
void Nuage::setId(int newId)
{
    id_ = newId;
}

char Nuage::getTexture() const { return texture_; }

const std::vector<IElement*>& Nuage::getEnfants() const
{
    return enfants_;
}

void Nuage::ajouterElement(IElement* p)
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
    // Utiliser le Decorator pour appliquer la texture
    // Note: Les decorators sont crees mais pas enregistres dans le Manager
    // car cette methode n'a pas acces au Manager
    // Les decorators sont geres localement dans le Nuage
    for (auto e : enfants_)
    {
        auto pts = e->getPoints();
        for (auto p : pts)
        {
            if (p)
            {
                TextureDecoratorConcret* decorator = new TextureDecoratorConcret(p, t);
                decorators_.push_back(decorator);
            }
        }
    }
}

void Nuage::afficher() const
{
    std::cout << id_ << ": Nuage '" << texture_
         << "' contient les elements: ";

    for (auto e : enfants_)
    {
        if (auto p = dynamic_cast<PointMD*>(e))
            std::cout << p->getId() << " ";
        else if (auto n = dynamic_cast<Nuage*>(e))
            std::cout << n->getId() << " ";
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
