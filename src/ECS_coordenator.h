#ifndef COORDENATOR_H
#define COORDENATOR_H

#include <set>
#include <utility>
#include <vector>

#include "ECS_entity.h"
#include "ECS_pool.h"
#include "component/component.h"
#include "util/types.h"

class Coordenator {
  private:
    /* Total number of entities. */
    usize numEntities;
    /* Entities to be added in the next update. */
    std::set<Entity> pendingEntitiesA;
    /* Entities to be killed in the next update. */
    std::set<Entity> pendingEntitiesK;

    std::vector<Pool *> c_pool;

  public:
    void update();

    usize newEntity();

    /**
     *
     */
    template <typename T>
    T &getComponent(Entity entity);
    /**
     *
     */
    template <typename T>
    bool hasComponent(Entity entity);
    /**
     *
     */
    template <typename T, typename... TArgs>
    void addComponent(Entity entity, TArgs &&...args) {
        // THIS FUNCTION HAVE AN MEMORY LEAK

        if (Component<T>::getID() > this->c_pool.size()) {
            this->c_pool.resize(entity.getID() + 1, nullptr);
        }

        // Ensure the component is added to the component pool if
        // not already present.
        if (!this->c_pool[Component<T>::getID()]) {
            PoolIMPL<T> *cPool = new PoolIMPL<T>();
            this->c_pool[Component<T>::getID()] = cPool;
        }

        PoolIMPL<T> *cPool = PoolIMPL<T>(this->c_pool[Component<T>::getID()]);
        if (entity.getID() > cPool->size()) {
            cPool.resize(this->numEntities);
        }

        // TODO: TEST IT!!!!
        T newC(std::forward<TArgs>(args)...);
        cPool->set(entity.getID(), newC);
    }
    /**
     *
     */
    template <typename T>
    void removeComponent(Entity entity);
};

#endif // COORDENATOR_H
