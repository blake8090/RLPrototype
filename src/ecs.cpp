#include "ecs.h"

#include <assert.h>
#include <iostream>
#include <memory>
#include <typeindex>

void Entity::add_component( Component* component )
{
    std::unique_ptr<Component> pointer( component );
    std::type_index info = typeid( *component );
    components.insert( std::make_pair( info.name(), move( pointer ) ) );
}

Entity::~Entity() {}

int EntityManager::create_entity()
{
    set_next_id();
    int id = next_id;
    Entity* e = new Entity();
    e->id = id;
    entities[next_id] = std::unique_ptr<Entity>( e );

    return id;
}

Entity* EntityManager::get_entity( int id )
{
    if ( id >= MAX_ENTITIES ) {
        return nullptr;
    }
    std::unique_ptr<Entity>& pointer = entities.at( id );
    return pointer.get();
}

void EntityManager::remove_entity( int id )
{
    std::unique_ptr<Entity>& pointer = entities.at( id );
    pointer.reset();
    entities[id] = nullptr;
    available_ids.push( id );
}

void EntityManager::set_next_id()
{
    if ( available_ids.empty() ) {
        next_id++;
    } else {
        next_id = available_ids.front();
        available_ids.pop();
    }
}

EntityManager::~EntityManager() {}