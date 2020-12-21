#include <iostream>
#include <fstream>  // Use ifstream
#include <vector>
#include <string>

class file_to_argv {
  /* A container to store argvs in vector and use destructor to automatically
     free the memory 
  */
 private:
  std::vector<const char*> argv;  // store the parameters

 public:
  /* constructors and destructors */
  file_to_argv();  // default constructor
  explicit file_to_argv(const char* filename);  // single parameter
  ~file_to_argv();

  /* Public methods*/
  void print_argv();  // print out parameters line by line
  std::vector<const char*> return_argv();  // return argv (deep copy)
};
