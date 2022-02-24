#include <iostream>
#include <memory>
#include <variant>
#include <functional>
#include <optional>

#include "../immer/flex_vector.hpp"
#include "helper.hpp"

using immer::flex_vector;
using std::function;
using std::pair;
using std::optional;

namespace parser {

struct state {
  int idx;
  flex_vector<char> text;
};

void flex_vector_print(flex_vector<char> vec) {
  for (const char c: vec) {
    std::cout << c;
  }
}

void state_print(state st) {
  auto tail = st.text.drop(st.idx);
  flex_vector_print(tail);
}

template <class T>
using Reply = pair<optional<T>, state>;

template <class T>
using Parser = function<Reply<T>(state)>;

// TODO test
template <class T>
Parser<T> choice(flex_vector<Parser<T>> parsers) {
  return
    [=](state st) {
      for (auto parser: parsers) {
        auto [result, state] = parser(st);
        if (result) {
          return pair(result, state);
        }
      }
      Reply<char> ret = pair(std::nullopt, st);
      return ret;
    };
}

// TODO test
template <class T>
Parser<flex_vector<T>> many(Parser<T> parser) {
  return
    [=](state st) {
      flex_vector<T> ret = {};
      auto [result, state] = parser(st);
      while (result) {
        ret = std::move(ret).push_back(result.value());
        Reply<T> reply = parser(state);
        result = reply.first;
        state = reply.second;
      }
      return pair(ret, state);
    };
}

// TODO test
Parser<char> range(char first, char last) {
  return
    [=](state st) {
      if (st.idx < st.text.size()) {
        auto c = st.text[st.idx];
        if (first <= c && c <= last) {
          state new_st = {st.idx++, std::move(st.text).drop(1)};
          return pair<optional<char>, state>(c, new_st);
        } else {
          return pair<optional<char>, state>(std::nullopt, st);
        }
      } else {
        return pair<optional<char>, state>(std::nullopt, st);
      }
    };
}

// TODO test this
Parser<char> one(char c) {
  return
    [=](state st) {
      if (st.idx < st.text.size()) {
        return pair<optional<char>, state>(std::nullopt, st);
      } else {
        auto read_char = st.text[st.idx];
        if (read_char == c) {
          state new_st = {st.idx++, st.text};
          return pair<optional<char>, state>(read_char, new_st);
        } else {
          return pair<optional<char>, state>(std::nullopt, st);
        }
      }
    };
}

// TODO test this
Reply<std::monostate> eof(state st) {
  if (st.idx >= st.text.size()) {
    return pair<optional<std::monostate>, state>(std::monostate(), st);
  } else {
    return pair<optional<std::monostate>, state>(std::nullopt, st);
  }
}


};
