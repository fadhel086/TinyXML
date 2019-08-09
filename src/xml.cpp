#include <iostream>
#include <fstream>
#include <string>
#include "../include/xml.h"

/*
 * class Xml2str
 */
// Constructor, Opens file
Xml2str::Xml2str(std::string file) : filename(file), infile(filename){
  // Init variables
  docType = XML_TYPE::DOCUMENT;
  if (!infile) {
    std::cerr << "Couldn't open the file" << std::endl;
    opStatus = OP_STATUS::FILE_OPEN_FAILED;
  } else {
    opStatus = OP_STATUS::FILE_OPEN_SUCCESS;
  }
}

// Fetch the contents from xml_file to string
std::string Xml2str::fetchString()
{
  if (opStatus != OP_STATUS::FILE_OPEN_SUCCESS) {
    xml_str.clear();
    return xml_str;
  }

  char c;
  while(infile.get(c)) {
    xml_str += c;
  }
  opStatus = OP_STATUS::FILE_EOF;

  return xml_str;
}

// Parse Implementation as it's a pure virtual function
std::string Xml2str::Parse(std::string& str) {

  // blank function, not used
  return std::string();
}

// return the fetched string
std::string Xml2str::getString() { return xml_str; }

Xml2str::~Xml2str() { ; }
// class Xml2str end
// ****************************************************************************************

/*
 * class XmlDeclaration
 */

XmlDeclaration::XmlDeclaration()
{
  version.clear();
  encoding.clear();
  standalone.clear();
  decl_str.clear();
}

std::string XmlDeclaration::getVersion() { return version; }
std::string XmlDeclaration::getEncoding() { return encoding; }
std::string XmlDeclaration::getStandalone() { return standalone; }
std::string XmlDeclaration::getDeclaration() { return decl_str; }
std::string XmlDeclaration::Parse(std::string& doc)
{

  if ((doc.find("<?xml") != std::string::npos) & (doc.find("?>") != std::string::npos)) {
    // Declaration found
    declaration = true;
    decl_str = doc.substr(doc.find("<?xml"), (doc.find("?>") + 2));

    // Get the version;
    XmlAttribute attrib(decl_str);
    std::string temp = "version=";
    version = attrib.Parse(temp);

    if (decl_str.find("encoding")) {
      temp = "encoding=";
      encoding = attrib.Parse(temp);
    }

    if (decl_str.find("standalone")) {
      temp = "standalone=";
      standalone = attrib.Parse(temp);
    }
    return decl_str;
    
  } else {
    declaration = false;
    decl_str.clear();
    return decl_str;
  }    
}
// class XmlDeclaration
// ****************************************************************************************

/*
 * class XmlAttribute
 */

XmlAttribute::XmlAttribute(std::string& element)
{
  /*
   * Declaration should be of below form:
   * <?xml version="1.0" ?> OR
   * <?xml version="1.0" encoding="UTF-8" standalone="yes|no" ?>
   */
  this->element = element;
}
std::string XmlAttribute::Parse(std::string& attrib)
{
  std::string temp;
  char delim;
  size_t pos = element.find(attrib) + attrib.length();
  delim = element[pos]; // attribute could be between single or double quotes
  
  // now pos will point to start of attribute
  ++pos;
  while (element[pos] != delim) {
    temp += element[pos++];
  }
  return temp;;
}

// class XmlAttribute
// ******************************************************************************************

/*
 * class XmlParser
 */

//XmlElement *XmlParser::root = new XmlElement;
XmlParser::XmlParser()
{
  root = new XmlElement;
  parent = nullptr;
  spaceCnt = 0;
  enteredPreviously = false;
}

XmlElement* XmlParser::getRoot() { return root; }

std::string XmlParser::Parse(std::string& xml_string)
{

  xml_str = xml_string;
  iter = xml_str.begin();
if (xml_str.find("<?xml") != std::string::npos) {
    // Declaration found and move to start of root node, +2 (move past '>\n' -- end of declaration)
    iter += xml_str.find(">") + 2;
  } else {
    // No declaration found, Move to start of root node
    iter += xml_str.find("<");
  }

  // Root is found at xml_str.begin() + it
  while (iter < xml_str.end())
    {
      // Create a string from iter to xml_str end;
      tempStr = std::string(iter, xml_str.end());
      spaceCnt = count(tempStr.begin(), tempStr.begin() + tempStr.find("<"), ' ');
      switch(spaceCnt) {
      case XML_NODE::ROOT:
	{
	  // Will come here twice, once at the beginning of root and towards the end of xml file
	  if (!enteredPreviously) {
	    parent = root;
	    root->parent = nullptr;
	    root->elem_string = tempStr;
	    std::cout << root->elem_string;
	    enteredPreviously = true;
	  }
	  break;
	}
      case XML_NODE::CHILD:
	{
	  XmlElement *child = new XmlElement;
	  child->parent = root;
	  child->elem_string = std::string(iter, iter + tempStr.find("\n"));
	  child->elem_string.erase(child->elem_string.begin(),
						  child->elem_string.begin() + spaceCnt);
	  parent = child;
	  child->parent->children.push_back(child);
	  break;
	}
      case XML_NODE::GRAND_CHILD:
	{
	  XmlElement *grandChild = new XmlElement;
	  grandChild->parent = parent;
	  grandChild->elem_string = std::string(iter, iter + tempStr.find("\n"));
	  grandChild->elem_string.erase(grandChild->elem_string.begin(),
						  grandChild->elem_string.begin() + spaceCnt);
	  grandChild->parent->children.push_back(grandChild);
	  break;
	}
      default:
	std::cout << "Not Supported\n";
	;
      }
      // Advance the iter to next line
      iter += tempStr.find("\n") + 1;
    }

  // Not used, returned as we are implementing a pure virtual function.
  return std::string();
}

//TBD: free the root and child elements here
XmlParser::~XmlParser()
{
  ;
}

// class XmlParser
// **********************************************************************************************
