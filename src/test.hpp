#include <string>
#include <variant>

namespace test {

// TODO add elapsed time?
struct Ok {
  std::monostate placeholder;
};

struct Error {
  std::string message;
};

using Result = std::variant<Ok, Error>;

}
