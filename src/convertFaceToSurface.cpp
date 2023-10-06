#include <iostream>

#include "TopoDS.hxx"
#include "TopoDS_Wire.hxx"
#include "TopoDS_Face.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "Geom_Circle.hxx"
#include "gp_Circ.hxx"


int main(int argc, char *argv[])
{   
    // Make a face from circle
    Standard_Real aRadius = 5;
    gp_Dir yDir(0,1,0);
    gp_Pnt aPnt3(0,0,0);

    gp_Circ baseCircle(gp_Ax2(aPnt3,yDir),aRadius);
    Handle(Geom_Circle) anCircle = new Geom_Circle(baseCircle);

    TopoDS_Edge edgeOfCircle = BRepBuilderAPI_MakeEdge(anCircle);
    TopoDS_Wire wireFromCircle = BRepBuilderAPI_MakeWire(edgeOfCircle);
    TopoDS_Face face = BRepBuilderAPI_MakeFace(wireFromCircle);

    // Convert
    BRepAdaptor_Surface toSurface(face);
    GeomAdaptor_Surface adaptSurface = toSurface.Surface();
    Handle(Geom_Surface) aSurface = adaptSurface.Surface();

    return 0;
}