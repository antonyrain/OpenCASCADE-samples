#include "BRepBuilderAPI_MakeEdge.hxx"
#include "TColgp_Array1OfPnt.hxx"
#include "Geom_BezierCurve.hxx"
#include "TopoDS_Edge.hxx"

int main(int argc, char *argv[])
{
	TColgp_Array1OfPnt controlPoints(1,3);
	controlPoints.SetValue(1,gp_Pnt(5, 0, 24));
	controlPoints.SetValue(2,gp_Pnt(12.5, 0, 17));	
	controlPoints.SetValue(3,gp_Pnt(12.5, 0, 10));	
	
	Handle_Geom_Curve bezierCurve = new Geom_BezierCurve(controlPoints);

    BRepBuilderAPI_MakeEdge edgeMaker;
	edgeMaker.Init(bezierCurve);	
	TopoDS_Shape anEdge1 = edgeMaker.Shape(); // TopoDS_Shape
	// or
	// TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(bezierCurve);

	return 0;
}