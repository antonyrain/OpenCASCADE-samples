#include <iostream>

#include "TopoDS.hxx"
#include "TopoDS_Wire.hxx"
#include "TopoDS_Face.hxx"
#include "gp_Circ.hxx"
#include "Geom_Circle.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "TColgp_Array1OfPnt.hxx"
#include "Geom_BezierCurve.hxx"
#include "GeomFill_Pipe.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "GeomAPI_IntSS.hxx"


int main(int argc, char *argv[])
{
    Standard_Real aRadius = 5;
    Standard_Real aPlaneR = 10;

    gp_Dir yDir(0,1,0);

    gp_Pnt aPnt1(0,-10,0);
    gp_Pnt aPnt2(0,10,0);
    gp_Pnt aPnt3(0,0,0);

    gp_Circ baseCircle1(gp_Ax2(aPnt1,yDir),aRadius);
    gp_Circ baseCircle2(gp_Ax2(aPnt2,yDir),aRadius);
    gp_Circ baseCircle3(gp_Ax2(aPnt3,yDir),aPlaneR);
    
    Handle(Geom_Circle) anCircle1 = new Geom_Circle(baseCircle1);
    Handle(Geom_Circle) anCircle2 = new Geom_Circle(baseCircle2);
    Handle(Geom_Circle) anCircle3 = new Geom_Circle(baseCircle3);

    TopoDS_Edge edgeOfPlane = BRepBuilderAPI_MakeEdge(anCircle3);
    TopoDS_Wire wireOfPlane = BRepBuilderAPI_MakeWire(edgeOfPlane);
    TopoDS_Face aPlane = BRepBuilderAPI_MakeFace(wireOfPlane);

    TColgp_Array1OfPnt pathPoles(1, 2);
    pathPoles(1) = gp_Pnt(0, -10, 0);
    pathPoles(2) = gp_Pnt(0, 10, 0);

    Handle(Geom_BezierCurve) path = new Geom_BezierCurve(pathPoles);
    GeomFill_Pipe Pipe(path, aRadius);
    Pipe.Perform();
    Handle(Geom_Surface) aPipeSurf = Pipe.Surface();

    BRepAdaptor_Surface toSurface(aPlane);
    GeomAdaptor_Surface adaptSurface = toSurface.Surface();
    Handle(Geom_Surface) aSurface = adaptSurface.Surface();

    GeomAPI_IntSS anIntersection(aPipeSurf, aSurface, 0.001);
    Handle(Geom_Curve) aCurve = anIntersection.Line(1);
    return 0;
}