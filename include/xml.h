#ifndef XML_H
#define XML_H

#include <fstream>
#include <string>

class Xml2str {
private:
  const std::string filename;
  std::string xml_str;
  std::ifstream infile;
  
public:
  enum {
    FILE_OPEN_SUCCESS,
    FILE_OPEN_FAILED,
    FILE_EOF
  };
  int status;

  Xml2str(std::string file);
  std::string fetchString();
  std::string getString();
  ~Xml2str();
};

#endif // XML_H
