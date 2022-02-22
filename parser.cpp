#include <memory>
#include <variant>
#include <functional>
#include <optional>

#include "immer/flex_vector.hpp"
#include "visitor.hpp"

namespace parser {
struct parser_state {
  int idx;
  char* text;
};

//using rser = std::function<std::pair<T, parser_state>(parser_state)>;
template <class T>
using Box = std::shared_ptr<T>;

template <class T>
using Parser = std::function<std::pair<std::optional<T>, parser_state>(parser_state)>;

template <class T>
Parser<T> many(immer::flex_vector<Parser<T>> parsers) {
  return
    [&](const parser_state st) {
      for (auto parser: parsers) {
        auto [result, state] = parser(st);
        if (result.has_value()) {
          return std::pair(result, state);
        }
      }
      return std::pair(std::nullopt, st);
    };
}

};

int main() {
  return 0;
}
