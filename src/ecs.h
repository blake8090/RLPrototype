#pragma once

#include <map>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int MAX_ENTITIES = 1024;

struct Component {
    virtual ~Component() = default;
};

struct Entity {
    ~Entity();

    int id = 0;
    std::map<std::string, std::unique_ptr<Component>> components;

    void add_component( Component* component );

    template <typename T>
    T* get_component()
    {
        std::string index = typeid( T ).name();
        auto iterator = components.find( index );
        if ( iterator == components.end() ) {
            return nullptr;
        }
        auto& c = iterator->second;
        return static_cast<T*>( c.get() );
    }
};

class EntityManager
{
  public:
    EntityManager() : entities( MAX_ENTITIES ) {}
    ~EntityManager();

    int create_entity();
    Entity* get_entity( int id );
    void remove_entity( int id );

  private:
    int next_id = -1;

    std::queue<int> available_ids;
    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::string, int> component_type_ids;

    void set_next_id();
};
