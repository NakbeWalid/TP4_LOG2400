#include "invoker.h"

void Invoker::executer(Commande *cmd)
{
    cmd->executer();
    undoStack.push(cmd);

    while (!redoStack.empty())
        redoStack.pop();
}

void Invoker::undo()
{
    if (undoStack.empty())
        return;

    Commande *cmd = undoStack.top();
    undoStack.pop();

    cmd->annuler();
    redoStack.push(cmd);
}

void Invoker::redo()
{
    if (redoStack.empty())
        return;

    Commande *cmd = redoStack.top();
    redoStack.pop();

    cmd->executer();
    undoStack.push(cmd);
}
