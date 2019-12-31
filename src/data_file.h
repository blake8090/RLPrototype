#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace data_file {

enum class value_type {
    String,
    Integer,
    Boolean,
    Float
};

struct value {
    std::vector<std::string> raw_values;
    value_type type = value_type::String;
};

struct node {
    std::map<std::string, value> values;

    std::string get_string(const std::string& key, const std::string& default_value = "");
    std::vector<std::string> get_strings(const std::string& key);

    int get_int(const std::string& key, int default_value = 0);
    //std::vector<int> get_ints( const std::string& key );

    //bool get_boolean( const std::string& key, bool default_value = false );
    //std::vector<bool> get_booleans( const std::string& key );

    //float get_float( const std::string& key, float default_value = 0.0f );
    //std::vector<float> get_floats( const std::string& key );
};

struct root {
    // TODO: map?
    std::vector<node> nodes;
};

class parser {
public:
    parser(const std::string& c)
        : content(c)
    {
    }
    ~parser(){};

    std::vector<node> parse();

private:
    int index = 0;
    const std::string& content;
    std::vector<node> nodes;
    node currentNode;

    void parse_node();
    void parse_key_value();

    bool eof();
    void eat_whitespace();
    std::string read_until(char until);
    bool next_char_is(char c);
    void save_current_node();
};

} // namespace data_file