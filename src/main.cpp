#include "application.hpp"
#include <exception>

int main(int argc, char *argv[])
{
  try
  {
    Application application;
    application.run();
  }
  catch (std::exception const &ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  return 0;
}
