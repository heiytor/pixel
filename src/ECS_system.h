#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

#include "ECS_entity.h"
#include "component/component.h"
#include "util/types.h"

const u64 MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class System {
  private:
    Signature signature;
    std::vector<Entity> entities;

  public:
    System() = default;
    ~System() = default;

    void addEntity(Entity entity);
    void removeEntity(Entity entity);
    const std::vector<Entity> &getEntities() const;
    const Signature &getSignature() const;

    template <typename T>
    void requireComponent() {
        const auto component = Component<T>::getID();
        this->signature.set(component.id);
    };
};

#endif // ECS_H
