#include "invoker.h"

void Invoker::executer(Commande *cmd)
{
    cmd->executer();     // fait l’action
    undoStack.push(cmd); // on l’ajoute à l’historique

    // Dès qu’on fait une nouvelle action, on efface redo
    while (!redoStack.empty())
        redoStack.pop();
}

void Invoker::undo()
{
    if (undoStack.empty())
        return;

    Commande *cmd = undoStack.top();
    undoStack.pop();

    cmd->annuler();      // annule l’effet
    redoStack.push(cmd); // on la met dans redo
}

void Invoker::redo()
{
    if (redoStack.empty())
        return;

    Commande *cmd = redoStack.top();
    redoStack.pop();

    cmd->executer();     // refait l’action
    undoStack.push(cmd); // revient dans undo
}