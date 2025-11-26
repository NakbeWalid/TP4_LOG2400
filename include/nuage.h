#pragma once
#include <vector>
#include "point.h"

class Nuage {
public:
    Nuage(int id, char texture = 'o');

    void ajouterPoint(PointMD* p);
    void retirerPoint(int id);

    int getId() const;
    char getTexture() const;

    void appliquerTexture(char t);
    const std::vector<PointMD*>& getPoints() const;

    void afficher() const;

private:
    int id_;
    char texture_;
    std::vector<PointMD*> points_;
};
