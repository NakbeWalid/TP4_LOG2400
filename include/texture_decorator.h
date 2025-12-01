#pragma once
#include "IElement.h"
#include "point.h"
#include <vector>

// ============================================
// PATRON DECORATOR - Classe abstraite Decorator
// ============================================
// Cette classe est la classe de base abstraite pour tous les decorators.
// Elle herite de IElement (Component) et contient une reference a un IElement.
// Elle delegue les appels de base a l'element enveloppe.
class TextureDecorator : public IElement
{
protected:
    IElement* element_;  // Reference au Component enveloppe

public:
    TextureDecorator(IElement* elem) : element_(elem) {}
    virtual ~TextureDecorator() = default;

    // Methodes de base deleguees a l'element (delegation)
    void afficher() const override
    {
        if (element_)
            element_->afficher();
    }

    void afficherDansGrille(std::vector<std::vector<char>>& grille, bool afficherID) const override
    {
        if (element_)
            element_->afficherDansGrille(grille, afficherID);
    }

    std::vector<PointMD*> getPoints() const override
    {
        if (element_)
            return element_->getPoints();
        return {};
    }

    // Methodes virtuelles pures pour les fonctionnalites specifiques au decorator
    virtual void appliquerTexture(char texture) = 0;
    virtual void retirerTexture(char texture) = 0;
};
