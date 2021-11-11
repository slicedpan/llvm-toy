#include <exception>

class ParserError : std::exception {
  public:
    ParserError(const char* msg) : message(msg) {}
    const char* what() {
      return this->message.c_str();
    }
  private:
    std::string message;
};