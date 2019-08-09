#include "../include/xml.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // exit()
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

  string file("../test_files/test.xml");

  Xml2str doc{file};
  
  std::string xml_str = doc.fetchString();

  XmlDeclaration decl;
  decl.Parse(xml_str);

  std::string temp = xml_str;
  std::string declaration = decl.getDeclaration();

  //XmlElement *root = getRoot(xml_str);
  XmlParser myParser;
  myParser.Parse(xml_str);

  XmlElement *root = myParser.getRoot();
  
  // Iterate to test the functionality
    if (!root->elem_string.empty()) {
    // Data present in root.
    if (!root->children.empty()) {
      std::vector<XmlElement *>::iterator iter = root->children.begin();
      for (iter; iter < root->children.end(); ++iter)
	{
	  std::cout << (*iter)->elem_string << std::endl;
	  if (!(*iter)->children.empty()){
	    std::vector<XmlElement *>::iterator child_iter = (*iter)->children.begin();
	    for(child_iter; child_iter < (*iter)->children.end(); ++child_iter)
	      {
		std::cout <<  "  " << (*child_iter)->elem_string << std::endl;
	      }
	  }
	}
    }
  }
  
  return 0;

}
