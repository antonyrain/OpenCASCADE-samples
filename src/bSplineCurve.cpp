#include <iostream>
#include "TColgp_Array1OfPnt.hxx"
#include "Geom_BSplineCurve.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"

int main(int argc, char *argv[])
{
    Standard_Integer Degree = 2;

    TColgp_Array1OfPnt Poles(0,2);
    Poles.SetValue( 0, gp_Pnt(-5. , 0, 24.) );
    Poles.SetValue( 1, gp_Pnt(-12.5, 0, 17.75) );
    Poles.SetValue( 2, gp_Pnt(-12.5, 0, 10.) );

    // Knots -- Degree + NbPoles + 1 = 6
    Standard_Integer NbKnots = 6;
    TColStd_Array1OfReal Knots(1,NbKnots);
    int i;
    for( i=1; i<=NbKnots; i++ )
        Knots(i) = i - 1;

    // Multiplicities
    TColStd_Array1OfInteger Mults(1,NbKnots);
    for( i=1; i<=NbKnots; i++ )
        Mults(i) = 1;

    Handle(Geom_BSplineCurve) hBSpline;
    try
    {
    hBSpline = new Geom_BSplineCurve(Poles, Knots, Mults, Degree);
    }catch(Standard_ConstructionError& e)
    {
        std::cout << e.GetMessageString() << std::endl;
    }

    BRepBuilderAPI_MakeEdge edgeMaker;
	edgeMaker.Init(hBSpline);	
	TopoDS_Shape anEdge1 = edgeMaker.Shape(); // TopoDS_Shape

    return 0;
}