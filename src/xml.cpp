#include <iostream>
#include <fstream>
#include <string>
#include "../include/xml.h"

// Constructor, Opens file
Xml2str::Xml2str(std::string file) : filename(file), infile(filename) {
  if (!infile) {
    std::cerr << "Couldn't open the file" << std::endl;
    status = FILE_OPEN_FAILED;
  } else {
    status = FILE_OPEN_SUCCESS;
  }
}

// Get the string from xml_file
std::string Xml2str::fetchString() {
  if (status != FILE_OPEN_SUCCESS) {
    return std::string();
  }

  char c;
  while(infile.get(c)) {
    xml_str += c;
  }
  status = FILE_EOF;

  return xml_str;
}

// return the fetched string
std::string Xml2str::getString() { return xml_str; }

Xml2str::~Xml2str() { ; }
