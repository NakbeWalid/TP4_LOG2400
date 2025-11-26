#pragma once
#include <vector>
#include "point.h"

class Nuage {
public:
    Nuage(int id, char texture = ' ');

    // Gestion des points
    void ajouterPoint(PointMD* p);
    void retirerPoint(int id);

    // Accès
    int getId() const;
    char getTexture() const;
    const std::vector<PointMD*>& getPoints() const;

    // Modification
    void appliquerTexture(char t);

    // Affichage (format TP)
    void afficher() const;

private:
    int id_;
    char texture_;                 // texture du nuage
    std::vector<PointMD*> points_; // enfants (Composite simple)
};
