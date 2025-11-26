#include "cmd_deplacer.h"

CmdDeplacer::CmdDeplacer(PointMD *p, int nx, int ny)
    : point(p), oldX(p ? p->getX() : 0), oldY(p ? p->getY() : 0), newX(nx), newY(ny)
{
}

void CmdDeplacer::executer()
{
    if (point)
        point->setPosition(newX, newY);
}

void CmdDeplacer::annuler()
{
    if (point)
        point->setPosition(oldX, oldY);
}