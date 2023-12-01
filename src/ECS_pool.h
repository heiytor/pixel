#ifndef POOL_H
#define POOL_H

#include <vector>

#include "util/types.h"

class Pool {
  public:
    virtual ~Pool() {}
};

template <typename T>
class PoolIMPL : public Pool {
  private:
    std::vector<T> data;

  public:
    PoolIMPL(usize size) {
        data.resize(size);
    }

    virtual ~PoolIMPL() = default;

    /**
     * Resizes the pool's data maximum size.
     */
    void resize(usize size) {
        this->data.resize(size);
    }

    /**
     * Erases the pool's data.
     */
    void clear() {
        this->data.clear();
    }

    /**
     * Returns `true` when the pool's data is empty, `false` otherwise.
     */
    bool isEmpty() const {
        return this->data.empty();
    }

    /**
     * Returns the filled size of the pool's data.
     */
    usize size() const {
        return this->data.size();
    }

    void push(T obj) {
        this->data.push_back(obj);
    }

    void set(usize idx, T obj) {
        this->data[idx] = obj;
    }

    T &getIndex(usize idx) {
        return this->data[idx];
    }
};

#endif // POOL_H
