#ifndef XML_H
#define XML_H

#include <fstream>
#include <string>
#include <cstddef>
#include <vector>
#include <algorithm>

/*
 * class XmlBase
 */
class XmlBase {
 public:
  enum OP_STATUS {
    DEFAULT, FILE_OPEN_SUCCESS, FILE_OPEN_FAILED,
    FILE_EOF, INVALID_XML_TYPE
  };
  int opStatus = DEFAULT;

  // May eliminate in future, as the present excercise may not require this.
  enum XML_TYPE {
    DOCUMENT, ELEMENT, DECLARATION,
    NODE, COMMENT, UNKNOWN
  };
  int docType = UNKNOWN;
  
  enum XML_NODE {
    ROOT,
    CHILD = 2,
    GRAND_CHILD = 4
  };

  virtual std::string Parse(std::string& str) = 0;
};
// class XmlBase end
// ********************************************************************************************

/*
 * class Xml2str
 */
class Xml2str : public XmlBase {
 private:
  const std::string filename;
  std::string xml_str;
  std::ifstream infile;

 public:
  Xml2str(std::string file);
  std::string fetchString();
  std::string getString();
  std::string Parse(std::string& str);
  ~Xml2str();
};
// class Xml2str end
// *********************************************************************************************

/*
 * class XmlDeclaration
 */
class XmlDeclaration : public XmlBase {

 private:
  std::string version;
  std::string encoding;
  std::string standalone;
  std::string decl_str;
  bool declaration;

 public:
  XmlDeclaration();
  std::string Parse(std::string& doc);
  std::string getVersion();
  std::string getEncoding();
  std::string getStandalone();
  std::string getDeclaration();
};
// class XmlDeclaration end
// *********************************************************************************************

/*
 * class XmlAttribute
 */
class XmlAttribute : public XmlBase {

 private:
  std::string element;
  
 public:
  XmlAttribute(std::string& element);
  std::string Parse(std::string& attrib);

};
// class XmlAttribute
// **********************************************************************************************

/*
 * class XmlParser
 */

class XmlElement {
public:
  XmlElement *parent;
  std::string elem_string;
  std::vector <XmlElement *> children;
};

class XmlParser :public XmlBase {
 private:
  XmlElement *root;
  XmlElement *parent;
  std::string xml_str, tempStr;
  std::string::iterator iter;
  unsigned int spaceCnt;
  bool enteredPreviously;

 public:
  XmlParser();
  std::string Parse(std::string& xml_string);
  XmlElement * getRoot();
  ~XmlParser();
  
};
// class XmlParser
// **********************************************************************************************
#endif // XML_H
