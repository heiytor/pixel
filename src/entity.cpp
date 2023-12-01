#include "entity.h"
#include "types_util.h"

Entity::Entity(usize id) : id(id) {
}

const usize Entity::getID() const {
    return this->id;
}
