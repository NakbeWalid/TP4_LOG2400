#pragma once
#include "texture_decorator.h"


class TextureDecoratorConcret : public TextureDecorator
{
private:
    char texture_;

public:
    TextureDecoratorConcret(IElement* elem, char texture) 
        : TextureDecorator(elem), texture_(texture)
    {
        appliquerTexture(texture);
    }

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

    void retirerTexture(char texture) override
    {
        auto pts = getPoints();
        for (auto p : pts)
        {
            if (p)
            {
            }
        }
    }

    char getTexture() const { return texture_; }
};
