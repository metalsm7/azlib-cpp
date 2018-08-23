//
// Created by leeyh on 2018-08-23.
//

#include <algorithm>
#include "azlib.h"

using namespace std;
using namespace azlib;

string azstring::trim(string const &source) {
  auto wsfront=find_if_not(source.begin(),source.end(),[](int c){return isspace(c);});
  return string(wsfront,find_if_not(source.rbegin(),string::const_reverse_iterator(wsfront),[](int c){return isspace(c);}).base());
}


string azstring::json::remove_inner(string const& source, char const& start_char, char const& end_char) {
  string rtn_value;
  //
  int dq_start_idx = -1, dq_end_idx = -1, idx = 0, prev_idx = 0;
  int start_chat_exist_after_dq_start = 0, idx_after_dq_start = -1;
  bool in_dq = false;
  while (true) {
    idx = in_dq ? source.find(end_char, idx) : source.find(start_char, idx);
    if (idx > -1) {
      if (idx == 0 || idx > 0 && source[idx - 1] != '\\') {
        if (in_dq) {
          idx_after_dq_start = source.find(start_char, start_chat_exist_after_dq_start == 0 ? (dq_start_idx + 1) : (idx_after_dq_start + 1));
          if (idx_after_dq_start > -1 && idx_after_dq_start < idx && source[idx_after_dq_start - 1] != '\\') {
            start_chat_exist_after_dq_start = 1;
            idx++;
            continue;
          }
          dq_end_idx = idx;
          in_dq = false;

          if (dq_end_idx > -1) {
            rtn_value.append(string(dq_end_idx - dq_start_idx - 1, ' '));
          }
        }
        else {
          dq_start_idx = idx;
          in_dq = true;
          rtn_value.append(source.substr(prev_idx, idx - prev_idx) + start_char);
        }
      }
      prev_idx = idx;
      idx++;
    }
    else {
      rtn_value.append(source.substr(dq_end_idx < 0 ? 0 : dq_end_idx));
      break;
    }
  }
  return rtn_value;
}

azdata azstring::json::to_azdata(string const& source) {
  return azdata(source);
}

azlist azstring::json::to_azlist(string const& source) {
  return azlist(source);
}