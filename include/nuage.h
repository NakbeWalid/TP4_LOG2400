#pragma once
#include <vector>
#include "IElement.h"
#include "point.h"

class TextureDecoratorConcret;

class Nuage : public IElement
{
public:
    Nuage(int id, char texture = ' ');
    ~Nuage();

    void ajouterElement(IElement* elem);
    void retirerPoint(int id);

    int getId() const;
    void setId(int newId);
    char getTexture() const;
    const std::vector<IElement*>& getEnfants() const;

    void appliquerTexture(char t);

    void afficher() const override;
    void afficherDansGrille(std::vector<std::vector<char>>& grille,
                            bool afficherID) const override;
    std::vector<PointMD*> getPoints() const override;

private:
    int id_;
    char texture_;
    std::vector<IElement*> enfants_;
    std::vector<TextureDecoratorConcret*> decorators_;
};
