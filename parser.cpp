#include <memory>
#include <variant>
#include <functional>
#include <optional>

#include "immer/flex_vector.hpp"
#include "helper.hpp"

using immer::flex_vector;
using std::function;
using std::pair;
using std::optional;
using std::string;

namespace parser {

struct parser_state {
  int idx;
  string& text;
};

template <class T>
using Parser = function<pair<optional<T>, parser_state>(parser_state)>;

// TODO test
template <class T>
Parser<T> choice(flex_vector<Parser<T>> parsers) {
  return
    [=](parser_state st) {
      for (auto parser: parsers) {
        auto [result, state] = parser(st);
        if (result) {
          return pair(result, state);
        }
      }
      return pair(std::nullopt, st);
    };
}

// TODO test
template <class T>
Parser<flex_vector<T>> many(Parser<T> parser) {
  return
    [=](parser_state st) {
      flex_vector<T> ret = {};
      auto result = parser(st);
      while (result.first) {
        ret = std::move(ret).push_back(result.first.value());
        result = parser(result.second);
      }
      return pair(ret, result.second);
    };
}

// TODO test
Parser<std::monostate> range(char first, char last) {
  return
    [=](parser_state st) {
      if (st.idx < st.text.size()) {
        return pair<std::optional<std::monostate>, parser_state>(std::nullopt, st);
      } else {
        auto c = st.text[st.idx];
        if (first <= c && c <= last) {
          parser_state new_st = {st.idx++, st.text};
          return pair<std::optional<std::monostate>, parser_state>(std::make_optional(std::monostate()), new_st);
        } else {
          return pair<std::optional<std::monostate>, parser_state>(std::nullopt, st);
        }
      }
    };
}

};
