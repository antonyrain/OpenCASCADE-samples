#include <iostream>

#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "GC_MakeSegment.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"


int main(int argc, char *argv[])
{
    gp_Pnt aPnt1(5., 0, 0);
    gp_Pnt aPnt2(0, 0, 0);

    Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(aPnt1, aPnt2);
    TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(aSegment);

    return 0;
}