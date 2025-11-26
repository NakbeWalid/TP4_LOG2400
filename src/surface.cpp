#include "surface.h"
#include <algorithm>
#include <cmath>

// ---------------------------
// STRATEGIE C1
// ---------------------------
std::vector<std::pair<PointMD*, PointMD*>> 
SurfaceC1::construire(const Nuage& n) const
{
    std::vector<std::pair<PointMD*, PointMD*>> lignes;
    auto pts = n.getPoints();

    if (pts.size() < 2)
        return lignes;

    // On trie par ID croissant
    std::vector<PointMD*> tri = pts;
    std::sort(tri.begin(), tri.end(), 
             [](PointMD* a, PointMD* b) { return a->getId() < b->getId(); });

    for (size_t i = 0; i < tri.size() - 1; ++i)
        lignes.push_back({ tri[i], tri[i+1] });

    return lignes;
}

// ---------------------------
// STRATEGIE C2
// Distance minimale (greedy)
// ---------------------------
static double dist(PointMD* a, PointMD* b) {
    return std::sqrt(
        std::pow(a->getX() - b->getX(), 2) + 
        std::pow(a->getY() - b->getY(), 2)
    );
}

std::vector<std::pair<PointMD*, PointMD*>> 
SurfaceC2::construire(const Nuage& n) const
{
    std::vector<std::pair<PointMD*, PointMD*>> lignes;
    auto pts = n.getPoints();

    if (pts.size() < 2)
        return lignes;

    std::vector<PointMD*> restants = pts;
    std::vector<PointMD*> ordre;

    // On commence par le point le plus bas en x
    std::sort(restants.begin(), restants.end(), 
             [](PointMD* a, PointMD* b) { return a->getX() < b->getX(); });

    ordre.push_back(restants[0]);
    restants.erase(restants.begin());

    // Greedy : toujours connecter au point le + proche
    while (!restants.empty()) {
        PointMD* dernier = ordre.back();
        PointMD* plusProche = restants[0];
        double meilleure = dist(dernier, plusProche);

        for (auto p : restants) {
            double d = dist(dernier, p);
            if (d < meilleure) {
                meilleure = d;
                plusProche = p;
            }
        }

        lignes.push_back({ dernier, plusProche });

        ordre.push_back(plusProche);
        restants.erase(std::remove(restants.begin(), restants.end(), plusProche), restants.end());
    }

    return lignes;
}
