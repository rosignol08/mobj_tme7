#include "Box.h"

namespace Netlist{

    LineShape::LineShape ( Symbol * owner , const Box & box )
    : Shape ( owner ) , box_ ( box )
    { }

    LineShape :: LineShape ( Symbol * owner , int x1 , int y1 , int x2 , int y2 )
    : owner_ ( owner ), x1_ ( x1 ), y1_ ( y1 ), x2_ ( x2 ), y2_ ( y2 )
    { owner_ -> add ( this ); }

    LineShape::~LineShape ()
    { }

    Box LineShape::getBoundingBox () const
    { return box_ ; }

    void LineShape::toXml(std::ostream& stream) {
			stream 	<< "<line x1=\"" << x1_ << "\""
                    << " y1=\"" << y1_ << "\""
                    << " x2=\"" << x2_ << "\""
                    << " y2=\"" << y2_ << "\"/>";
    }

    bool LineShape::fromXml (Symbol* owner, xmlTextReaderPtr reader) {
        xmlGetIntAttribute(reader, "x1", x1);
        xmlGetIntAttribute(reader, "y1", y1);
        xmlGetIntAttribute(reader, "x2", x2);
        xmlGetIntAttribute(reader, "y2", y2);
        LineShape* shape = new LineShape(owner, x1, y1, x2, y2);
        return shape;
    }
}