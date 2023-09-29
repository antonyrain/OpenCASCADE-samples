#include <iostream>

#include "TColgp_Array1OfPnt.hxx"
#include "GCPnts_UniformDeflection.hxx"
#include "Geom_BSplineCurve.hxx"
#include "GeomAdaptor_Curve.hxx"
#include "GCPnts_UniformAbscissa.hxx"


int main(int argc, char *argv[])
{
    Standard_Integer Degree = 2;

    // Poles
    TColgp_Array1OfPnt Poles(0,2);
    Poles.SetValue( 0, gp_Pnt(5. , 0, 24.) );
    Poles.SetValue( 1, gp_Pnt(12.5, 0, 17) );
    Poles.SetValue( 2, gp_Pnt(12.5, 0, 10.) );

    // Knots -- Degree + NbPoles + 1 = 6
    Standard_Integer NbKnots = 6;
    TColStd_Array1OfReal Knots(1,NbKnots);
    int i;
    for( i=1; i<=NbKnots; i++ )
        Knots(i) = i - 1;

    // Mults
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

    Standard_Integer NbPoints = 10;
    GeomAdaptor_Curve C (hBSpline);
    GCPnts_UniformAbscissa myAlgo(C, NbPoints);
    myAlgo.Initialize (C, NbPoints);
    if (myAlgo.IsDone())
    {
        Standard_Integer nbr = myAlgo.NbPoints();
        Standard_Real param;
        gp_Pnt p;
        for (Standard_Integer i = 1; i <= nbr; i++)
        {
            param = myAlgo.Parameter(i);
            C.D0(myAlgo.Parameter(i), p);
            //
            std::cout << " " << std::endl;
            std::cout << "Point coordinates:" << std::endl;
            std::cout << "  X: " << p.X() << "  Y: " << p.Y() << "  Z: " << p.Z() << std::endl;
        }
    }
    return 0;
}