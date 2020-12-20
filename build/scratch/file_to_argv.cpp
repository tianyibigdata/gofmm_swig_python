#include <iostream>
#include <fstream>  // Use ifstream
#include <vector>

std::vector<const char*> file_to_argv(const char* filename) {
  std::string line;
  std::vector<std::string> paras;
  int n_lines = 0;  // Number of parameters in total

  std::ifstream file(filename);  // read the entire file
  std::string   para;            // parameter <-> each line in file
  while (std::getline(file, para))  // Keep reading in each parameter
    paras.push_back(para);

  std::vector<const char*> argv;
  for (std::string const& str : paras) {
    argv.push_back(str.data());
  }


  return argv;
}


int main() {
  std::vector<const char*> parameters = file_to_argv("parameters.txt");

  // for (auto i = parameters.begin(); i != parameters.end(); ++i)
  //   std::cout << *i << '\n';
  std::cout << parameters[2] << '\n';

  return 0;
}
