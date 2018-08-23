//
// Created by leeyh on 2018-08-23.
//

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <typeinfo>

#ifndef AZLIB_CPP_AZLIB_H
#define AZLIB_CPP_AZLIB_H

#endif //AZLIB_CPP_AZLIB_H

using namespace std;
namespace azlib {
  class azdata {
    private:
    map<string, string> hash_map;
    map<string, string> hash_type_map;
    public:
    azdata() {}
    azdata(string const& json);
    ~azdata() {}
    void set(string const& key, azdata value);
    void set(string const& key, string const& value);
    void set(string const& key, float value);
    void set(string const& key, long value);
    void set(string const& key, int value);
    std::string get_type(string const& key);
    vector<string> get_keys();
    std::string get(string const& key);
    int get_int(string const& key, int default_value);
    int get_int(string const& key);
    std::string get_string(string const& key);
    std::string get_string(string const& key, string default_value);
    azdata get_data(string const& key);
    string to_json_string();
  };
  class azlist {
    private:
    vector<azlib::azdata> list;
    string name;
    public:
    azlist();
    azlist(string const& source);
    ~azlist();
    void add(azdata data);
    void add(azlist list);
    azdata get(int index);
    void remove(int index);
    void clear();
    size_t size();
    //
    std::string to_json_string();
    // properties
    void set_name(string name);
    std::string get_name();
  };
  class azstring {
    private:
    public:
    static string trim(string const& source);

    class json {
      private:
      public:
      static string remove_inner(string const &source, char const &start_char, char const &end_char);
      azdata to_azdata(string const &source);
      azlist to_azlist(string const &source);
    };
  };
}