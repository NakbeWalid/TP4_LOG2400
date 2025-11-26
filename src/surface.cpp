#include "surface.h"
#include <algorithm>
#include <cmath>

// ---------------------------
// STRATÉGIE C1 : ordre des IDs
// ---------------------------
std::vector<Ligne> SurfaceC1::construire(const Nuage& n) const
{
    std::vector<Ligne> lignes;
    auto pts = n.getPoints();

    if (pts.size() < 2)
        return lignes;

    // Tri selon les IDs
    std::vector<PointMD*> tri = pts;
    std::sort(tri.begin(), tri.end(),
              [](PointMD* a, PointMD* b) { return a->getId() < b->getId(); });

    for (size_t i = 0; i < tri.size() - 1; ++i)
        lignes.push_back({ tri[i], tri[i+1] });

    return lignes;
}

// ---------------------------
// Calcul distance
// ---------------------------
static double dist(PointMD* a, PointMD* b)
{
    return std::sqrt(
        std::pow(a->getX() - b->getX(), 2) +
        std::pow(a->getY() - b->getY(), 2)
    );
}

// ---------------------------
// STRATÉGIE C2 : chemin greedy
// ---------------------------
std::vector<Ligne> SurfaceC2::construire(const Nuage& n) const
{
    std::vector<Ligne> lignes;
    auto pts = n.getPoints();

    if (pts.size() < 2)
        return lignes;

    std::vector<PointMD*> restants = pts;

    // Démarre au point le plus bas en X
    std::sort(restants.begin(), restants.end(),
              [](PointMD* a, PointMD* b) { return a->getX() < b->getX(); });

    PointMD* courant = restants[0];
    restants.erase(restants.begin());

    while (!restants.empty()) {
        PointMD* plusProche = restants[0];
        double meilleure = dist(courant, plusProche);

        for (auto p : restants)
        {
            double d = dist(courant, p);
            if (d < meilleure)
            {
                meilleure = d;
                plusProche = p;
            }
        }

        lignes.push_back({ courant, plusProche });

        courant = plusProche;
        restants.erase(std::remove(restants.begin(),
                                   restants.end(),
                                   plusProche),
                       restants.end());
    }

    return lignes;
}
