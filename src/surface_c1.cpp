#include "surface_c1.h"
#include <algorithm>

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

    // Connecter les points consecutifs
    for (size_t i = 0; i < tri.size() - 1; ++i)
        lignes.push_back({ tri[i], tri[i+1] });

    // Fermer le polygone : connecter le dernier au premier
    if (tri.size() >= 3)
        lignes.push_back({ tri.back(), tri.front() });

    return lignes;
}

