#include "TopoDS_Shape.hxx"
#include "Geom_BezierSurface.hxx"
#include "TColgp_Array2OfPnt.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"


int main(int argc, char *argv[])
{
  	//Create a bezier surface from control points
	TColgp_Array2OfPnt controlPoints(1,3,1,3);

	controlPoints.SetValue(1,1,gp_Pnt(-5.0,-5.0,0.0));
	controlPoints.SetValue(2,1,gp_Pnt(0.0,-5.0,0.0));
	controlPoints.SetValue(3,1,gp_Pnt(5.0,-5.0,0.0));

	controlPoints.SetValue(1,2,gp_Pnt(-5.0,0.0,0.0));
	controlPoints.SetValue(2,2,gp_Pnt(0.0,0.0,5.0));
	controlPoints.SetValue(3,2,gp_Pnt(5.0,0.0,0.0));

	controlPoints.SetValue(1,3,gp_Pnt(-5.0,5.0,0.0));
	controlPoints.SetValue(2,3,gp_Pnt(0.0,5.0,0.0));
	controlPoints.SetValue(3,3,gp_Pnt(5.0,5.0,0.0));

	Handle_Geom_BezierSurface surface = new Geom_BezierSurface(controlPoints);

	//Create a TopoDS_Shape out of the Bezier surface
	TopoDS_Shape face = BRepBuilderAPI_MakeFace(surface, 0.001);

	return 0;
}