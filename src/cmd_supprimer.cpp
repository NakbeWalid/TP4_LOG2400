#include "cmd_supprimer.h"
#include <algorithm>

CmdSupprimer::CmdSupprimer(std::vector<IElement*>& container,
                           IElement* elem)
    : container_(container),
      element_(elem),
      oldIndex_(0)
{
    auto it = std::find(container_.begin(), container_.end(), element_);
    if (it != container_.end())
        oldIndex_ = std::distance(container_.begin(), it);
}

void CmdSupprimer::executer()
{
    container_.erase(
        std::remove(container_.begin(), container_.end(), element_),
        container_.end()
    );
}

void CmdSupprimer::annuler()
{
    if (oldIndex_ > (int)container_.size())
        oldIndex_ = (int)container_.size();

    container_.insert(container_.begin() + oldIndex_, element_);
}
