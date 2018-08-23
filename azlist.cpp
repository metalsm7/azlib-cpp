//
// Created by leeyh on 2018-08-23.
//

#include "azlib.h"

using namespace std;
using namespace azlib;

azlist::azlist() {}
azlist::azlist(std::string const& source) {
  std::string trimed_source = azstring::trim(source);
  if (trimed_source[0] == '[' && trimed_source[trimed_source.size() - 1] == ']') {
    trimed_source = azstring::trim(trimed_source.substr(1, trimed_source.size() - 2));
    std::string rm_dq_str = azstring::json::remove_inner(trimed_source, '"', '"');
    std::string rm_m_str = azstring::json::remove_inner(rm_dq_str, '[', ']');
    std::string rm_str = azstring::json::remove_inner(rm_m_str, '{', '}');
    //cout << "trimed_source: " << trimed_source << endl;
    //cout << "rm_dq_str: " << rm_dq_str << endl;
    //cout << "rm_m_str: " << rm_m_str << endl;
    //cout << "rm_str: " << rm_str << endl;

    int idx = 0, pre_idx = 0;
    while (true) {
      idx = rm_str.find_first_of(',', idx);
      if (idx > -1 || (idx == -1 && pre_idx > 0)) {
        std::string data_str;
        if (idx > -1) {
          data_str = trimed_source.substr(pre_idx, idx - pre_idx);
        }
        else if (idx == -1) {
          data_str = trimed_source.substr(pre_idx + 1);
        }
        data_str = azstring::trim(data_str);
        if (data_str[0] == ',') data_str = azstring::trim(data_str.substr(1));
        if (data_str[data_str.size() - 1] == ',') data_str = azstring::trim(data_str.substr(0, data_str.size() - 1));

        //cout << "key:" << key << endl;
        //
        if (data_str[0] == '{') {
          this->add(azdata(data_str));
        }

        if (idx == -1) break;
        pre_idx = idx;
        idx++;
      }
      else {
        if (pre_idx < 1 && idx < 0) {
          std::string data_str;
          data_str = azstring::trim(rm_str);
          if (data_str.length() > 1 && data_str[0] == '{') {
            this->add(azdata(trimed_source));
          }
        }
        break;
      }
    }
  }
}
azlist::~azlist() {}

void azlist::add(azdata data) {
  this->list.push_back(data);
}

void azlist::add(azlist list) {
  for (int cnti=0; cnti<this->list.size(); cnti++) {
    this->add(list.get(cnti));
  }
}

azdata azlist::get(int index) {
  return this->list.at(index);
}

void azlist::remove(int index) {
  this->list.erase(this->list.begin() + index);
}

void azlist::clear() {
  this->list.clear();
}

size_t azlist::size() {
  this->list.size();
}

std::string azlist::to_json_string() {
  std::string rtn_value;
  rtn_value.append("[");
  for (int cnti=0; cnti<this->size(); cnti++) {
    if (cnti > 0) rtn_value.append(", ");
    rtn_value.append(this->get(cnti).to_json_string());
  }
  rtn_value.append("]");
  return rtn_value;
}