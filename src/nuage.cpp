#include "nuage.h"
#include <iostream>
#include <algorithm>

Nuage::Nuage(int id, char texture)
    : id_(id), texture_(texture)
{
}

int Nuage::getId() const {
    return id_;
}

char Nuage::getTexture() const {
    return texture_;
}

const std::vector<PointMD*>& Nuage::getPoints() const {
    return points_;
}

void Nuage::ajouterPoint(PointMD* p) {
    if (!p)
        return;
    points_.push_back(p);
}

void Nuage::retirerPoint(int id) {
    auto it = std::remove_if(points_.begin(), points_.end(),
                             [id](PointMD* p) {
                                 return p && p->getId() == id;
                             });
    points_.erase(it, points_.end());
}

void Nuage::appliquerTexture(char t) {
    // Met à jour la texture principale du nuage
    texture_ = t;

    // Et ajoute cette texture à tous les points du nuage
    for (auto p : points_) {
        if (p)
            p->addTexture(t);   // <<< ADAPTATION ICI (plus de setTexture)
    }
}

void Nuage::afficher() const {
    std::cout << "Nuage '" << texture_
              << "' contient les points: ";

    for (size_t i = 0; i < points_.size(); ++i) {
        if (points_[i])
            std::cout << points_[i]->getId();
        else
            std::cout << "x"; // point supprimé
        if (i + 1 < points_.size())
            std::cout << ", ";
    }

    std::cout << std::endl;
}
