#ifndef COMPONENT_H
#define COMPONENT_H

#include "../util/types.h"

class __BaseComponent {
  protected:
    static usize nextID;
};

template <typename T>
class Component : public __BaseComponent {
    static usize getID() {
        static usize id = nextID++;
        return id;
    }
};

#endif // COMPONENT_H
