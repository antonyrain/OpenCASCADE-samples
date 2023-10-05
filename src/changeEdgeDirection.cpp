#include <iostream>

#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "GC_MakeSegment.hxx"
#include "BRep_Tool.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"


int main(int argc, char *argv[])
{
    gp_Pnt aPnt1(5., 0, 0);
    gp_Pnt aPnt2(0, 0, 0);

    Handle(Geom_TrimmedCurve) aSegment = GC_MakeSegment(aPnt1, aPnt2);
    TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(aSegment);

    Standard_Real first, last;
    Handle(Geom_Curve) curve = BRep_Tool::Curve(anEdge, first, last);
    first = curve->ReversedParameter(first);
    last = curve->ReversedParameter(last);
    TopoDS_Edge edgeReversed = BRepBuilderAPI_MakeEdge(curve->Reversed(), last, first);

    return 0;
}