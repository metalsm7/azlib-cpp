//
// Created by leeyh on 2018-08-23.
//

#include "azlib.h"

using namespace std;
using namespace azlib;

azdata::azdata(string const &json) {
  string trimed_source = azstring::trim(json);
  if (trimed_source[0] == '{' && trimed_source[trimed_source.size() - 1] == '}') {
    trimed_source = azstring::trim(trimed_source.substr(1, trimed_source.size() - 2));
    string rm_dq_str = azstring::json::remove_inner(trimed_source, '"', '"');
    string rm_m_str = azstring::json::remove_inner(rm_dq_str, '[', ']');
    string rm_str = azstring::json::remove_inner(rm_m_str, '{', '}');
    //cout << "trimed_source: " << trimed_source << endl;
    //cout << "rm_dq_str: " << rm_dq_str << endl;
    //cout << "rm_m_str: " << rm_m_str << endl;
    //cout << "rm_str: " << rm_str << endl;

    int idx = 0, pre_idx = 0;
    while (true) {
      idx = rm_str.find_first_of(',', idx);
      if (idx == -1 && pre_idx == 0) {
        string data_str;
        data_str = azstring::trim(trimed_source);

        int key_value_idx = data_str.find_first_of(':');
        string key = azstring::trim(data_str.substr(0, key_value_idx));
        string value_string = azstring::trim(data_str.substr(key_value_idx + 1));

        if (key[0] == '"' || key[0] == '\'') {
          key = key.substr(1, key.size() - 2);
        }
        //
        if (value_string[0] == '{') {
          this->set(key, azdata(value_string));
        }
        else if (value_string[0] == '[') {
          //rtn_value.set<string>(key, "array!");
        }
        else if (value_string[0] == '"' || value_string[0] == '\'') {
          this->set(key, value_string.substr(1, value_string.size() - 2));
          //cout << "key: " << key << " / vakue: " << value << endl;
        }
        else {
          this->set(key, value_string);
        }
        break;
      }
      else if (idx > -1 || (idx == -1 && pre_idx > 0)) {
        string data_str;
        if (idx > -1) {
          data_str = trimed_source.substr(pre_idx, idx - pre_idx);
        }
        else if (idx == -1) {
          data_str = trimed_source.substr(pre_idx + 1);
        }
        data_str = azstring::trim(data_str);
        if (data_str[0] == ',') data_str = azstring::trim(data_str.substr(1));
        if (data_str[data_str.size() - 1] == ',') data_str = azstring::trim(data_str.substr(0, data_str.size() - 1));

        int key_value_idx = data_str.find_first_of(':');
        string key = azstring::trim(data_str.substr(0, key_value_idx));
        string value_string = azstring::trim(data_str.substr(key_value_idx + 1));
        if (key[0] == '"' || key[0] == '\'') {
          key = key.substr(1, key.size() - 2);
        }
        //cout << "key:" << key << endl;
        //
        if (value_string[0] == '{') {
          this->set(key, azdata(value_string));
        }
        else if (value_string[0] == '[') {
          //rtn_value.set<string>(key, "array!");
        }
        else if (value_string[0] == '"' || value_string[0] == '\'') {
          string value = value_string.substr(1, value_string.size() - 2);
          this->set(key, value);
          //cout << "key: " << key << " / vakue: " << value << endl;
        }
        else {
          this->set(key, value_string);
        }

        if (idx == -1) break;
        pre_idx = idx;
        idx++;
      }
      else {
        break;
      }
    }
  }
}

void azdata::set(string const& key, azdata value) {
  string value_type(typeid(value).name());
  //
  this->hash_type_map.erase(key);
  this->hash_type_map.insert(pair<string, string>(key, value_type));
  //
  this->hash_map.erase(key);
  this->hash_map.insert(pair<string, string>(key, value.to_json_string()));
}
void azdata::set(string const& key, string const& value) {
  string value_type(typeid(value).name());
  //
  this->hash_type_map.erase(key);
  this->hash_type_map.insert(pair<string, string>(key, value_type));
  //
  this->hash_map.erase(key);
  this->hash_map.insert(pair<string, string>(key, value));
}
void azdata::set(string const& key, float value) {
  string value_type(typeid(value).name());
  //
  this->hash_type_map.erase(key);
  this->hash_type_map.insert(pair<string, string>(key, value_type));
  //
  this->hash_map.erase(key);
  this->hash_map.insert(pair<string, string>(key, to_string(value)));
}
void azdata::set(string const& key, long value) {
  string value_type(typeid(value).name());
  //
  this->hash_type_map.erase(key);
  this->hash_type_map.insert(pair<string, string>(key, value_type));
  //
  this->hash_map.erase(key);
  this->hash_map.insert(pair<string, string>(key, to_string(value)));
}
void azdata::set(string const& key, int value) {
  string value_type(typeid(value).name());
  //
  this->hash_type_map.erase(key);
  this->hash_type_map.insert(pair<string, string>(key, value_type));
  //
  this->hash_map.erase(key);
  this->hash_map.insert(pair<string, string>(key, to_string(value)));
}
vector<string> azdata::get_keys() {
  vector<string> rtn_value;
  int idx = 0;
  for(std::map<string, string>::const_iterator it = this->hash_map.begin(); it != this->hash_map.end(); it++) {
    string key = it->first;
    rtn_value.push_back(key);
    idx++;
  }
  return rtn_value;
}
string azdata::get(string const& key) {
  if (this->hash_map.find(key) == this->hash_map.end()) {
    return "";
  }
  //cout << "get.1:" << this->hash_map.at(key) << endl;
  //cout << "get.2:" << *(string*)this->hash_map.at(key) << endl;
  return this->hash_map.at(key);
}

string azdata::get_type(string const& key) {
  return this->hash_type_map.at(key);
}

int azdata::get_int(string const& key) {
  return this->get_int(key, 0);
}

int azdata::get_int(string const& key, int default_value) {
  if (this->hash_map.find(key) == this->hash_map.end()) {
    return default_value;
  }
  return atoi(this->hash_map.at(key).c_str());
}

string azdata::get_string(string const& key) {
  return this->get_string(key, "");
}

string azdata::get_string(string const& key, string default_value) {
  if (this->hash_map.find(key) == this->hash_map.end()) {
    return default_value;
  }
  return this->hash_map.at(key);
}

azdata azdata::get_data(string const& key) {
  //azdata rtn_value;
  //rtn_value.from(this->hash_map.at(key));
  //cout << "get_data:" << this->hash_map.at(key) << endl;
  //cout << "get_data:" << rtn_value.get("sk1") << endl;
  //cout << "get_data:" << rtn_value.get("sk2") << endl;
  //cout << "get_data:" << rtn_value.get("sk3") << endl;
  return azdata(this->hash_map.at(key));
}

string azdata::to_json_string() {
  string rtn_value;
  rtn_value.append("{");
  int idx = 0;
  for(std::map<string, string>::const_iterator it = this->hash_map.begin(); it != this->hash_map.end(); it++) {
    string key = it->first;
    string value = it->second;
    string value_type = this->hash_type_map.at(key);
    //cout << "value_type:" << value_type << endl;
    //
    if (idx > 0) rtn_value.append(", ");
    if (value_type.find("basic_string", 0) != string::npos && value_type.substr(0, 2).compare("PA") != 0) {
      rtn_value.append("\"" + key + "\": \"" + value + "\"");
    }
    else if (value_type.find("azdata", 0) != string::npos && value_type.substr(0, 2).compare("PA") != 0) {
      rtn_value.append("\"" + key + "\": " + value);
    }
    else if (value_type.compare("Pi") == 0 || value_type.compare("i") == 0) {
      rtn_value.append("\"" + key + "\": " + value);
    }
    else if (value_type.compare("Pl") == 0 || value_type.compare("l") == 0) {
      rtn_value.append("\"" + key + "\": " + value);
    }
    else if (value_type.compare("Pf") == 0 || value_type.compare("f") == 0) {
      rtn_value.append("\"" + key + "\": " + value);
    }
    //
    idx++;
  }
  rtn_value.append("}");
  return rtn_value;
}