#pragma once
#include "affichage_template.h"
#include "point.h"
#include <vector>

// Classe concrete pour l'affichage par IDs
// Implemente le patron Template Method
class AffichageID : public AffichageTemplate
{
private:
    std::vector<std::vector<char>> grille_;

protected:
    void initialiserGrille() override
    {
        grille_ = std::vector<std::vector<char>>(HAUTEUR, std::vector<char>(LARGEUR, ' '));
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
            int id = p->getId();
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille_[y][x] = (id < 10 ? '0' + id : '*');
        }
    }

    void tracerLignes() override
    {
        // Tracer les lignes C1
        if (lignesC1_)
        {
            for (const auto& L : *lignesC1_)
                if (L.a && L.b)
                    tracerLigne(grille_,
                                L.a->getX(), L.a->getY(),
                                L.b->getX(), L.b->getY());
        }

        // Tracer les lignes C2
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
        // Re-afficher les IDs par-dessus les traits
        for (auto e : *elements_)
        {
            PointMD* p = dynamic_cast<PointMD*>(e);
            if (!p)
                continue;

            int x = p->getX();
            int y = p->getY();
            int id = p->getId();
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                grille_[y][x] = (id < 10 ? '0' + id : '*');
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
        // Rien a faire pour les IDs
    }
};

