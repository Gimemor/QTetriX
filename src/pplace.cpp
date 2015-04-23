#include "pplace.h"

pplace::pplace():width(0),height(0)
{}
void pplace::incX()
{ ++width; }
void pplace::decX()
{ --width; }
int pplace::x() const
{ return width; }
int pplace::y() const
{ return height; }
void pplace::set(int xx,int yy)
{ width=xx; height=yy; }
void pplace::incY()
{++height;}
