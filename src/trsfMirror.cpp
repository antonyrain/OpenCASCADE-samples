#include <iostream>

#include "gp.hxx"
#include "gp_Ax2.hxx"
#include "gp_Trsf.hxx"
#include "TopoDS_Shape.hxx"
#include "BRepPrimAPI_MakeCylinder.hxx"
#include "BRepBuilderAPI_Transform.hxx"


int main(int argc, char *argv[])
{   
    Standard_Real X = 0, Y = -25, Z = 0; 
    gp_Ax2 axes = gp::ZOX(); 
    axes.Translate(gp_Vec(X,Y,Z));
    TopoDS_Shape aCylinder = BRepPrimAPI_MakeCylinder(axes,5,50.0,0);

    gp_Ax1 xAxis = gp::OX();
    gp_Trsf aTrsf;
 
    aTrsf.SetMirror(xAxis);
    BRepBuilderAPI_Transform aBRepTrsf(aCylinder, aTrsf);
    TopoDS_Shape mirroredShape = aBRepTrsf.Shape();

    return 0;
}