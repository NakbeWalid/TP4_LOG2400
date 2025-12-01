#pragma once
#include <vector>
#include "point.h"
#include "nuage.h"

struct Ligne {
    PointMD* a;
    PointMD* b;
};

class SurfaceStrategy {
public:
    virtual ~SurfaceStrategy() = default;
    virtual std::vector<Ligne> construire(const Nuage& n) const = 0;
};

