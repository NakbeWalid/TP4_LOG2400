#pragma once
#include <stack>
#include "commande.h"

class Invoker
{
private:
    std::stack<Commande *> undoStack; 
    std::stack<Commande *> redoStack;

public:
    void executer(Commande *cmd); 
    void undo();                  
    void redo();                  
};