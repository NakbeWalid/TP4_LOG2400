#pragma once
#include "affichage_template.h"
#include "point.h"
#include <vector>
#include <string>

class AffichageTexture : public AffichageTemplate
{
private:
    std::vector<std::vector<std::string>> grille_;

protected:
    void initialiserGrille() override
    {
        grille_ = std::vector<std::vector<std::string>>(HAUTEUR, std::vector<std::string>(LARGEUR, " "));
    }

    void dessinerElements() override
    {
        for (auto e : *elements_)
        {
            PointMD* p = dynamic_cast<PointMD*>(e);
            if (!p)
                continue;

            int x = p->getX();
            int y = p->getY();
            if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
                continue;

            const auto& texs = p->getTextures();
            if (texs.empty())
            {
                grille_[y][x] = ".";
            }
            else
            {
                std::string s;
                for (char t : texs)
                    s.push_back(t);
                grille_[y][x] = s;
            }
        }
    }

    void tracerLignes() override
    {
        if (lignesC1_)
        {
            for (const auto& L : *lignesC1_)
                if (L.a && L.b)
                    tracerLigne(grille_,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());
        }

        if (lignesC2_)
        {
            for (const auto& L : *lignesC2_)
                if (L.a && L.b)
                    tracerLigne(grille_,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());
        }
    }

    void reDessinerElements() override
    {
        for (auto e : *elements_)
        {
            PointMD* p = dynamic_cast<PointMD*>(e);
            if (!p)
                continue;

            int x = p->getX();
            int y = p->getY();
            if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR)
                continue;

            const auto& texs = p->getTextures();
            if (texs.empty())
            {
                grille_[y][x] = ".";
            }
            else
            {
                std::string s;
                for (char t : texs)
                    s.push_back(t);
                grille_[y][x] = s;
            }
        }
    }

    void imprimer() override
    {
        for (int y = HAUTEUR - 1; y >= 0; --y)
        {
            for (int x = 0; x < LARGEUR; ++x)
                std::cout << grille_[y][x];
            std::cout << "\n";
        }
    }

    void postTraitement() override
    {
    }
};
