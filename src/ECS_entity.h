#ifndef ENTITY_H
#define ENTITY_H

#include "util/types.h"

class Entity {
  private:
    usize id;

  public:
    Entity(usize id);
    const usize getID() const;
};

#endif // ENTITY_H
