#pragma once
#include <vector>
#include "IElement.h"
#include "point.h"

// Forward declaration
class TextureDecoratorConcret;

class Nuage : public IElement
{
public:
    Nuage(int id, char texture = ' ');
    ~Nuage();

    // Gestion des enfants (points ou sous-nuages)
    void ajouterElement(IElement* elem);
    void retirerPoint(int id);

    // Accès
    int getId() const;
    void setId(int newId);
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
    std::vector<TextureDecoratorConcret*> decorators_; // Pour stocker les decorators
};
