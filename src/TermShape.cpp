#include "TermShape.h"

namespace Netlist{

  TermShape::TermShape ( Symbol * owner , string name , int x1 , int y1 )
    : Shape ( owner ) , term_ ( NULL ), x1_ ( x1 ), y1_ ( y1 )
  {
    Cell * cell = getCell ();
    term_ = cell -> getTerm ( name );
  }

  TermShape::~TermShape () { }

  Box TermShape :: getBoundingBox () const
  { return Box ( x1_ , y1_ , x1_ , y1_ ); }

  void TermShape::toXml(std::ostream& stream) {
		stream 	<< "<term x1=\"" << X1() << "\""
					<< " y1=\"" << x1_ << "\""
					<< " x2=\"" << y1_ << "\""
					<< " align=\"" << align_ << "\"/>";
	}

	bool TermShape::fromXml (Symbol* owner, xmlTextReaderPtr reader) {
		NameAlign name_align;
    string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
		xmlGetIntAttribute(reader, "x1", x1);
		xmlGetIntAttribute(reader, "y1", y1);
		string align = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ) );
  
    if      (align == "top_right")    { name_align = TopRight; }
    else if (align == "top_left")     { name_align = TopLeft; }
    else if (align == "bottom_left")  { name_align = BottomLeft; }
    else if (align == "bottom_right") { name_align = BottomRight; }

		TermShape* shape = new TermShape(owner, name, x1, y1, name_align);
		return shape;
	}
}