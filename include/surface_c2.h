#pragma once
#include "surface_strategy.h"

class SurfaceC2 : public SurfaceStrategy {
public:
    std::vector<Ligne> construire(const Nuage& n) const override;
};

