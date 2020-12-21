#include <iostream>
#include <fstream>  // Use ifstream
#include <vector>
#include <string>



class file_to_argv {
 private:
  std::vector<const char*> argv;

 public:
  /* constructors and destructors */
  file_to_argv();  // default constructor
  explicit file_to_argv(const char* filename);  // single parameter
  ~file_to_argv();
  std::vector<const char*> return_argv();

  /* Public methods*/
  void print_argv();
};

file_to_argv::file_to_argv() {}  // size 0 vector initialization

file_to_argv::file_to_argv(const char* filename) {
  /* Read file line by line into argv (public field) */

  /* Construct vector string */
  std::string line;
  std::vector<std::string> parameters;
  std::ifstream file(filename);  // read the entire file
  std::string   para;            // parameter <-> each line in file

  while (std::getline(file, para))  // Keep reading in each parameter
    parameters.push_back(para);

  /* Convert vector string to vector char* */
  // argv(parameters.size(), nullptr);
  for (int i=0; i < parameters.size(); i++)
    argv.push_back(parameters[i].c_str());

  parameters.clear();  // clear the vector
}

file_to_argv::~file_to_argv() {
  argv.clear();
}

void file_to_argv::print_argv() {
  for (auto i = argv.begin(); i != argv.end(); ++i)
    std::cout << *i << '\n';
}


std::vector<const char*> file_to_argv::return_argv() {
  return argv;
}

// std::vector<const char*> file_to_argv(const char* filename) {
//   std::string line;
//   std::vector<std::string> paras;

//   std::ifstream file(filename);  // read the entire file
//   std::string   para;            // parameter <-> each line in file
//   while (std::getline(file, para))  // Keep reading in each parameter
//     paras.push_back(para);

//   std::vector<const char*> argv;
//   for (std::string const& str : paras) {
//     argv.push_back(str.data());
//   }


//   return argv;
// }


int main() {
  file_to_argv a("parameters.txt");
  // a.print_argv();


  // std::vector<const char*> b = a.return_argv();
  // std::vector<const char*> parameters = file_to_argv("parameters.txt");

  // for (auto i = b.begin(); i != b.end(); ++i)
  //   std::cout << *i << '\n';
  // // std::cout << parameters[2] << '\n';

  return 0;
}
