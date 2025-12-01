#include "surface_c2.h"
#include <algorithm>
#include <cmath>

static double dist(PointMD* a, PointMD* b)
{
    return std::sqrt(
        std::pow(a->getX() - b->getX(), 2) +
        std::pow(a->getY() - b->getY(), 2)
    );
}

std::vector<Ligne> SurfaceC2::construire(const Nuage& n) const
{
    std::vector<Ligne> lignes;
    auto pts = n.getPoints();

    if (pts.size() < 2)
        return lignes;

    if (pts.size() == 2)
    {
        lignes.push_back({ pts[0], pts[1] });
        return lignes;
    }
    std::vector<PointMD*> restants = pts;
    PointMD* premier = nullptr;

    std::sort(restants.begin(), restants.end(),
              [](PointMD* a, PointMD* b) 
              { 
                  if (a->getX() != b->getX())
                      return a->getX() < b->getX();
                  return a->getY() < b->getY();
              });

    PointMD* courant = restants[0];
    premier = courant;
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

    if (premier && courant && premier != courant)
        lignes.push_back({ courant, premier });

    return lignes;
}

