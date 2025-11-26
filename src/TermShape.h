#include <iostream>
#include "Box.h"
#include "Symbol.h"
#include "Shape.h"

namespace Netlist{

  enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };

  class TermShape : public Shape {
    public :
                      TermShape       ( Symbol* owner, string name, int x , int y, NameAlign name_align = TopLeft);
                     ~TermShape       ();
              Box     getBoundingBox  () const ;
      inline  Term *  getTerm         () const ;
      inline  int     getX            () const ;
      inline  int     getY            () const ;
              void    toXml           (std::ostream&);
      static  bool    fromXml         (Symbol*, xmlTextReaderPtr);

    private :
      Term * term_ ;
      NameAling align_;
      int x_ , y_ ;
  };

  Term* TermShape::getTerm { return term_; };
  Term* TermShape::getX { return x_; };
  Term* TermShape::getY { return y_; };

}
