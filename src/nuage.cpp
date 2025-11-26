#include "nuage.h"
#include <iostream>

Nuage::Nuage(int id, char texture)
    : id_(id), texture_(texture)
{}

int Nuage::getId() const { return id_; }
char Nuage::getTexture() const { return texture_; }

const std::vector<PointMD*>& Nuage::getPoints() const {
    return points_;
}

void Nuage::ajouterPoint(PointMD* p) {
    points_.push_back(p);
}

void Nuage::retirerPoint(int id) {
    for (auto it = points_.begin(); it != points_.end(); ++it) {
        if ((*it)->getId() == id) {
            points_.erase(it);
            return;
        }
    }
}

void Nuage::appliquerTexture(char t) {
    texture_ = t;

    // Appliquer texture aux enfants (Composite simple)
    for (auto p : points_)
        p->setTexture(t);
}

void Nuage::afficher() const {
    std::cout << "Nuage #" << id_ << " texture='";

    if (texture_ == ' ')
        std::cout << "'";
    else
        std::cout << texture_ << "'";

    std::cout << std::endl;

    for (auto p : points_)
        p->afficher();
}