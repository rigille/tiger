#include "parser.hpp"

#include <iostream>

parser::Parser<flex_vector<char>> identifier_builder() {
  parser::Parser<char> uppercase_letter = parser::range('A', 'Z');
  parser::Parser<char> lowercase_letter = parser::range('a', 'z');
  parser::Parser<char> digit = parser::range('0', '9');
  parser::Parser<char> underscore = parser::one('_');
  parser::Parser<char> head_parser = parser::choice<char>(flex_vector<parser::Parser<char>>{uppercase_letter, lowercase_letter});
  parser::Parser<flex_vector<char>> tail_parser = parser::many(parser::choice(flex_vector<parser::Parser<char>>{uppercase_letter, lowercase_letter, digit, underscore}));
  return
    [=](parser::state st) {
      auto [head, st0] = head_parser(st);
      if (head) {
        auto [tail, st1] = tail_parser(st0);
        if (tail) {
          auto ret = std::move(tail.value()).push_front(head.value());
          return pair<optional<flex_vector<char>>, parser::state>(ret, st1);
        } else {
          return pair<optional<flex_vector<char>>, parser::state>(std::nullopt, st);
        }
      } else {
        return pair<optional<flex_vector<char>>, parser::state>(std::nullopt, st);
      }
    };
}

parser::Parser<flex_vector<char>> identifier = identifier_builder();


int main() {
  std::string str_text = "hello";
  auto flex_text = flex_vector<char>(str_text.begin(), str_text.end());
  std::cout << flex_text.size() << std::endl;
  parser::state init_state = {0, flex_text};
  parser::Reply<flex_vector<char>> reply = identifier(init_state);
  if (reply.first) {
    std::cout << "parseou" << std::endl;
    return 0;
  } else {
    std::cout << "não parseou" << std::endl;
    return 0;
  }
}
// identifiers
//
// skip
//
// decs
//
// tydec
//
// vardec
//
// fundec
//
//
