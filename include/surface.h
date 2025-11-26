#pragma once
#include <vector>
#include "point.h"
#include "nuage.h"

// Classe abstraite STRATEGY
class SurfaceStrategy {
public:
    virtual ~SurfaceStrategy() = default;

    // Génère une liste de paires (x0,y0,x1,y1) représentant les lignes à tracer
    virtual std::vector<std::pair<PointMD*, PointMD*>> 
        construire(const Nuage& n) const = 0;
};

// C1 : ordre des IDs
class SurfaceC1 : public SurfaceStrategy {
public:
    std::vector<std::pair<PointMD*, PointMD*>> 
        construire(const Nuage& n) const override;
};

// C2 : distance minimale
class SurfaceC2 : public SurfaceStrategy {
public:
    std::vector<std::pair<PointMD*, PointMD*>> 
        construire(const Nuage& n) const override;
};
