#pragma once
#include <vector>
#include "point.h"

class Nuage {
public:
    Nuage(int id, char texture = 'o');

    int getId() const;
    char getTexture() const;

    const std::vector<PointMD*>& getPoints() const;

    void ajouterPoint(PointMD* p);
    void retirerPoint(int id);

    // Applique une texture au nuage + aux points
    void appliquerTexture(char t);

    void afficher() const;

private:
    int id_;
    char texture_;                  // texture principale du nuage
    std::vector<PointMD*> points_;  // points dans ce nuage
};
