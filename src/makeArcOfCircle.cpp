#include "Standard_Real.hxx"
#include "Geom_Circle.hxx"
#include "Geom_TrimmedCurve.hxx"
#include "GC_MakeArcOfCircle.hxx"
#include "gp_Pnt.hxx"
#include "gp_Circ.hxx"

int main(int argc, char *argv[])
{
    Standard_Real aRadius = 5.;
    gp_Dir zDir(0,0,1);
    gp_Pnt aPnt(0,0,0);
    gp_Circ baseCircle(gp_Ax2(aPnt,zDir),aRadius);
    
    Handle(Geom_TrimmedCurve) anArcOfCircle;
    anArcOfCircle = new Geom_TrimmedCurve(new Geom_Circle(baseCircle),0,M_PI_2);
    
    return 0;
}