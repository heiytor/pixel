#include <spdlog/spdlog.h>

#include "ECS_coordenator.h"
#include "ECS_entity.h"
#include "util/types.h"

usize Coordenator::newEntity() {
    Entity entity(++this->numEntities);
    this->pendingEntitiesA.insert(entity);

    spdlog::info("A new entity with ID {} is awaiting insertion.", entity.getID());

    return entity.getID();
}

template <typename T>
T &getComponent(Entity entity) {}
template <typename T>
bool hasComponent(Entity entity) {}
template <typename T, typename... TArgs>
void addComponent(Entity entity, TArgs &&...args) {}
template <typename T>
void removeComponent(Entity entity) {}

void Coordenator::update() {
}
