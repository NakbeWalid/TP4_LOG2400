#pragma once

class Commande
{
public:
    virtual ~Commande() = default;

    virtual void executer() = 0;
    virtual void annuler() = 0;
};