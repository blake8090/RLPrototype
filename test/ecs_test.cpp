#include "catch/catch.hpp"
#include "ecs.h"

struct TestComponent : Component {
    int field = 0;
};

SCENARIO( "Create an entity with a component" )
{
    Entity e;
    TestComponent* c = new TestComponent();
    c->field = 4;

    e.add_component( c );
    TestComponent* result = e.get_component<TestComponent>();

    REQUIRE( result == c );
    REQUIRE( result->field == 4 );
}

SCENARIO( "Create and retrieve multiple entities" )
{
    EntityManager manager;

    int id1 = manager.create_entity();
    Entity* e1 = manager.get_entity( id1 );

    int id2 = manager.create_entity();
    Entity* e2 = manager.get_entity( id2 );

    REQUIRE( id1 == 0 );
    REQUIRE( e1 );
    REQUIRE( e1->id == 0 );

    REQUIRE( id2 == 1 );
    REQUIRE( e2 );
    REQUIRE( e2->id == 1 );
}

SCENARIO( "Remove an entity" )
{
    EntityManager manager;

    int id = manager.create_entity();
    Entity* e = manager.get_entity( id );

    manager.remove_entity( id );
    e = manager.get_entity( id );

    REQUIRE_FALSE( e );
}

SCENARIO( "Reuse deleted entity ids" )
{
    EntityManager manager;

    int id1 = manager.create_entity();
    int id2 = manager.create_entity();

    manager.remove_entity( id1 );
    manager.remove_entity( id2 );

    int id3 = manager.create_entity();
    Entity* e3 = manager.get_entity( id3 );

    int id4 = manager.create_entity();
    Entity* e4 = manager.get_entity( id4 );

    REQUIRE( id3 == 0 );
    REQUIRE( id4 == 1 );
}
