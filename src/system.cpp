#include "ECS.h"
#include "types_util.h"
#include <algorithm>
#include <cstdint>

void System::removeEntity(Entity entity) {
    this->entities.erase(std::remove_if(this->entities.begin(),
                                        this->entities.end(),
                                        [&entity](const Entity &other) {
                                            return entity.getID() == other.getID();
                                        }),
                         this->entities.end());
}

const std::vector<Entity> &System::getEntities() const {
    return this->entities;
}

const Signature &System::getSignature() const {
    return this->signature;
}
