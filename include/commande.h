#pragma once
#ifndef COMMANDE_H
#define COMMANDE_H

// Patron Command : prototypes et structures pour undo/redo
typedef struct Commande {
    void (*executer)(void* objet);
    void (*annuler)(void* objet);
    void* objet;
} Commande;

// Prototypes des fonctions de gestion de commandes ici

#endif // COMMANDE_H
Commande;
