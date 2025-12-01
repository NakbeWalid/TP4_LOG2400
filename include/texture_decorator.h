#pragma once
#include "IElement.h"
#include "point.h"
#include <vector>


class TextureDecorator : public IElement
{
protected:
    IElement* element_;

public:
    TextureDecorator(IElement* elem) : element_(elem) {}
    virtual ~TextureDecorator() = default;

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

    virtual void appliquerTexture(char texture) = 0;
    virtual void retirerTexture(char texture) = 0;
};
