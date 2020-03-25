#pragma once

#include <fluffy/pch.hpp>

namespace Fluffly {

/**
 * Internal
 */
class AbstractInstanceContainer
{
public:
    AbstractInstanceContainer()          = default;
    virtual ~AbstractInstanceContainer() = default;

    AbstractInstanceContainer& operator=(AbstractInstanceContainer&& other) noexcept
    {
        mRawPointer       = other.mRawPointer;
        other.mRawPointer = nullptr;

        return *this;
    }

    void* get() { return mRawPointer; }

protected:
    explicit AbstractInstanceContainer(void* ptr)
      : mRawPointer(ptr)
    {
    }

private:
    void* mRawPointer = nullptr;
};

/**
 * Internal
 */
template<class T>
class InstanceContainer : public AbstractInstanceContainer
{
public:
    explicit InstanceContainer(std::unique_ptr<T> ptr)
      : AbstractInstanceContainer(ptr.get())
      , mPointer(std::move(ptr))
    {
    }
    ~InstanceContainer() override = default;

private:
    std::unique_ptr<T> mPointer;
};

/**
 * Hold and manage pointers to different objects you need at various places in the code. The managed objects will
 * automatically be destroyed when the ServiceContainer is out of scope.
 *
 * // Create an object inside the container
 * serviceContainer.set<MyClass>(param1);
 * // Create an object that has a dependency on MyClass*:
 * serviceContainer.set<MyService, MyClass>();
 * // Get a pointer to an contained object:
 * MyService* s = serviceContainer.get<MyService>();
 */
class ServiceContainer
{
public:
    template<typename T, typename... Deps, typename... Args>
    void set(Args... args);

    template<typename T>
    void give(T* service);

    template<typename T>
    T* get() const;

    template<typename T>
    bool has() const;

private:
    template<typename T>
    int typeId() const;

private:
    static int                                                mLastTypeId;
    std::map<int, std::unique_ptr<AbstractInstanceContainer>> mContainer;
};
}

#include <fluffy/service/service_container.inl>
