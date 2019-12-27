#include "catch/catch.hpp"
#include "data_file.h"

SCENARIO( "Parse root node" )
{
    std::string content =
        R"(key = "value")";

    data_file::parser p( content );
    std::vector<data_file::node> nodes = p.parse();

    REQUIRE( nodes.size() == 1 );
    REQUIRE( nodes[0].get_string( "key" ) == "value" );
}

SCENARIO( "Parse multiple nodes" )
{
    std::string content =
        "[node]"
        R"(key = "value")"
        "[node]"
        R"(key2 = "value2")";

        data_file::parser p( content );
    std::vector<data_file::node> nodes = p.parse();

    REQUIRE( nodes.size() == 2 );
    REQUIRE( nodes[0].get_string( "key" ) == "value" );
    REQUIRE( nodes[1].get_string( "key2" ) == "value2" );
}

SCENARIO( "Parse string values" )
{
    std::string content =
        "[node]"
        R"(title = "The title")"
        R"(author = "Author")";

    data_file::parser p( content );
    std::vector<data_file::node> nodes = p.parse();

    REQUIRE( nodes.size() == 1 );
    REQUIRE( nodes[0].get_string( "title" ) == "The title" );
    REQUIRE( nodes[0].get_string( "author" ) == "Author" );
}