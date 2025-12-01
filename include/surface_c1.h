#pragma once
#include "surface_strategy.h"

class SurfaceC1 : public SurfaceStrategy {
public:
    std::vector<Ligne> construire(const Nuage& n) const override;
};

