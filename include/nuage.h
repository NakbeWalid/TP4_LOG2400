#pragma once
#include <vector>
#include "IElement.h"
#include "point.h"

class Nuage : public IElement
{
public:
    Nuage(int id, char texture = ' ');

    // Gestion des enfants (points ou sous-nuages)
    void ajouterElement(IElement* elem);
    void retirerPoint(int id);

    // Accès
    int getId() const;
    char getTexture() const;
    const std::vector<IElement*>& getEnfants() const;

    // Appliquer texture à tous les points du nuage
    void appliquerTexture(char t);

    // IElement
    void afficher() const override;
    void afficherDansGrille(std::vector<std::vector<char>>& grille,
                            bool afficherID) const override;
    std::vector<PointMD*> getPoints() const override;

private:
    int id_;
    char texture_;
    std::vector<IElement*> enfants_;
};
