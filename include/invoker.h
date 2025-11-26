#pragma once
#include <stack>
#include "commande.h"

class Invoker
{
private:
    std::stack<Commande *> undoStack; // Commandes déjà exécutées
    std::stack<Commande *> redoStack; // Commandes annulées (undo)

public:
    void executer(Commande *cmd); // exécuter une commande
    void undo();                  // annuler la dernière commande
    void redo();                  // réappliquer une commande annulée
};