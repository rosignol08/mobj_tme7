#include "Symbol.h"

namespace Netlist{
  Symbol::Symbol ( Cell* cell)
  : owner_(cell), shapes_(); {}

  Symbol::~Symbol() {}

  Cell* Symbol::getCell () { return owner_; }

  Box Symbol::getBoundingBox () {

  }

  Point getTermPosition (Term* term) {
    return term->getPosition();
  }

  TermShape* getTermShape ( Term* ) {

  }

  void add ( Shape* shape) {
    shapes_.push_back(shape);
  }

  void remove ( Shape* shape ) {
    for ( vector<Shape*>::iterator ishape=shapes_.begin() ; ishape != shapes_.end() ; ++ishape ) {
      if (*ishape == shape) shapes_.erase( ishape );
    }
  }

  void toXml ( std::ostream& stream) {
    stream << indent << "<symbol>\n";
    indent++;
    for (Shape* s: shapes_){
        s->toXml(stream);
    }
    stream << --indent << "</symbol>\n";
  }

  static Symbol* fromXml ( Cell* cell, xmlTextReaderPtr reader) {

    const xmlChar* symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol" );
    const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );

    Symbol* symbol = new Symbol(cell);

    while(true){
        int status = xmlTextReaderRead(reader);

        // Detects error of reading
        if (status != 1){
            if (status != 0) {
                cerr << "[ERROR] Symbol::fromXml(): Unexpected termination of the XML parser." << endl;
            }
            else cerr << "[ERROR] Symbol::fromXml(): </symbol> is missing but parser ended" << endl;
            break;
        }

        // Ignore comments and whitespaces
        switch ( xmlTextReaderNodeType(reader) ) {
            case XML_READER_TYPE_COMMENT:
            case XML_READER_TYPE_WHITESPACE:
            case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
        }

        if (nodeName == symbolTag && (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)) break;
        else if(Shape::fromXml(symbol, reader)) continue;
        break;
    }

    return symbol;
  }

}