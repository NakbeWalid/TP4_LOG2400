#pragma once
#include "commande.h"
#include "point.h"

class CmdDeplacer : public Commande
{
private:
    PointMD *point;
    int oldX, oldY;
    int newX, newY;

public:
    CmdDeplacer(PointMD *p, int nx, int ny);

    void executer() override;
    void annuler() override;
};