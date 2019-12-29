#include "data_file.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

static inline void rtrim( std::string& str )
{
    str.erase( std::find_if( str.rbegin(), str.rend(), []( int ch ) {
                   return !std::isspace( ch );
               } ).base(),
               str.end() );
}

namespace data_file
{

std::string node::get_string( const std::string& key, const std::string& default_value )
{
    std::string result = default_value;
    if ( values.find( key ) != values.end() ) {
        value& value = values[key];
        if ( value.type == value_type::String && !value.raw_values.empty() ) {
            result = value.raw_values[0];
        }
    }
    return result;
}

std::vector<std::string> node::get_strings( const std::string& key )
{
    if ( values.find( key ) != values.end() ) {
        value& value = values[key];
        if ( value.type == value_type::String ) {
            return value.raw_values;
        }
    }
    return std::vector<std::string>();
}

int node::get_int( const std::string& key, int default_value )
{
    int result = default_value;
    std::string raw_value = get_string( key );
    if ( !raw_value.empty() ) {
        std::stringstream ss( raw_value );
        ss >> result;
    }
    return result;
}

std::vector<node> parser::parse()
{
    while ( !eof() ) {
        eat_whitespace();
        if ( content[index] == '[' ) {
            parse_node();
        } else if ( std::isalpha( content[index] ) ) {
            parse_key_value();
        } else {
            // TODO: log unexpected error
            break;
        }
    }
    save_current_node();
    return nodes;
}

void parser::parse_node()
{
    // skip over '['
    index++;

    if ( eof() ) {
        // TODO: should throw error
        return;
    }

    std::string node_name = read_until( ']' );
    save_current_node();
    index++;
}

void parser::parse_key_value()
{
    std::string key = read_until( '=' );
    if ( eof() ) {
        // TODO: log unexpected EOF
        return;
    }
    rtrim( key );
    // skip '='
    index++;
    eat_whitespace();
    if ( eof() ) {
        return;
    }

    value val;
    std::string raw_value;

    if ( content[index] == '-' || std::isdigit( content[index] ) ) {
        val.type = value_type::String;
        raw_value += content[index];
        index++;
        while ( !eof() && content[index] != '\n' ) {
            raw_value += content[index];
            index++;
        }
    } else if ( content[index] == '"' ) {
        index++;
        raw_value = read_until( '"' );
        index++;
    } else {
        // TODO: throw error
    }

    val.raw_values.push_back( raw_value );
    currentNode.values.emplace( key, val );
}

bool parser::eof()
{
    return index >= content.size();
}

void parser::eat_whitespace()
{
    while ( !eof() && std::isspace( content[index] ) ) {
        index++;
    }
}

std::string parser::read_until( char until )
{
    std::string result;
    while ( !eof() && content[index] != until ) {
        result += content[index];
        index++;
    }
    return result;
}

bool parser::next_char_is( char c )
{
    int next_index = index + 1;
    if ( next_index > content.size() ) {
        return false;
    }
    return content[next_index] == c;
}

void parser::save_current_node()
{
    if ( !currentNode.values.empty() ) {
        nodes.push_back( currentNode );
        currentNode = node();
    }
}

} // namespace data_file
