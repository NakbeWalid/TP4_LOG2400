#pragma once
#include "texture_decorator.h"

// ============================================
// PATRON DECORATOR - ConcreteDecorator
// ============================================
// Cette classe est l'implementation concrete du decorator.
// Elle ajoute la fonctionnalite d'application de textures aux elements.
class TextureDecoratorConcret : public TextureDecorator
{
private:
    char texture_;  // La texture que ce decorator applique

public:
    TextureDecoratorConcret(IElement* elem, char texture) 
        : TextureDecorator(elem), texture_(texture)
    {
        appliquerTexture(texture);
    }

    // Implementation de la methode pour appliquer la texture
    void appliquerTexture(char texture) override
    {
        texture_ = texture;
        auto pts = getPoints();
        for (auto p : pts)
        {
            if (p)
                p->addTexture(texture);
        }
    }

    // Implementation de la methode pour retirer la texture
    void retirerTexture(char texture) override
    {
        auto pts = getPoints();
        for (auto p : pts)
        {
            if (p)
            {
                // Retirer la texture du point
                // Note: PointMD n'a pas de removeTexture, on doit l'ajouter ou gerer autrement
                // Pour l'instant, on ne fait rien car la logique actuelle ne le gere pas
            }
        }
    }

    char getTexture() const { return texture_; }
};

