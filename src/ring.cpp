#include <iostream>

#include <TopAbs.hxx>
#include "TopoDS.hxx"
#include "TopoDS_Wire.hxx"
#include "TopoDS_Shape.hxx"

#include "TColgp_SequenceOfPnt.hxx"
#include "TColgp_HSequenceOfPnt.hxx"
#include "TColgp_Array1OfPnt.hxx"

#include "BRepBuilderAPI_MakeWire.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepBuilderAPI_MakeShell.hxx"
#include "BRepBuilderAPI_MakeSolid.hxx"
#include "BRepAdaptor_Curve.hxx"
#include "GeomFill_NSections.hxx"
#include "GeomAdaptor_Curve.hxx" 
#include "GeomConvert.hxx"

#include "BRep_Tool.hxx"
#include "BRep_Builder.hxx"
#include "BRepCheck_Analyzer.hxx"
#include "BRepOffsetAPI_MakeThickSolid.hxx"
#include "BRepMesh_IncrementalMesh.hxx"
#include "BRepPrimAPI_MakeCylinder.hxx"
#include "BRepBuilderAPI_Transform.hxx"
#include "BRepAlgoAPI_Cut.hxx"

#include "Geom_Circle.hxx"
#include "Geom_Ellipse.hxx"
#include "Geom_BezierCurve.hxx"
#include "Geom_BSplineCurve.hxx"
#include "Geom_BSplineSurface.hxx"
#include "Geom_TrimmedCurve.hxx"

#include "GCPnts_UniformAbscissa.hxx"
#include "gp_Trsf.hxx"

#include "StlAPI_Writer.hxx"
#include "StlAPI.hxx"

int main(int argc, char *argv[])
{
    TColGeom_SequenceOfCurve curveSeq1;
    TColGeom_SequenceOfCurve curveSeq2;

    gp_Dir xDir(1,0,0);
    gp_Dir yDir(0,1,0);
    gp_Dir zDir(0,0,1);

    TColgp_Array1OfPnt Points1(0, 2);
    Points1.SetValue( 0, gp_Pnt(5., 0, 14) );
    Points1.SetValue( 1, gp_Pnt(12.5, 0, 10.) );
    Points1.SetValue( 2, gp_Pnt(12.5 , 0, 0) );

    TColgp_Array1OfPnt Points2(0, 4);
    Points2.SetValue( 0, gp_Pnt(0, 5., 14) );
    Points2.SetValue( 1, gp_Pnt(0, 8.5, 10) );
    Points2.SetValue( 2, gp_Pnt(0, 7, 5) );
    Points2.SetValue( 3, gp_Pnt(0, 6, 3) );
    Points2.SetValue( 4, gp_Pnt(0, 5, 0) );

	Handle_Geom_Curve bezierCurve1 = new Geom_BezierCurve(Points1);
    Handle_Geom_Curve bezierCurve2 = new Geom_BezierCurve(Points2);

    // Geting coordimates of points on bezierCurve1
    TColgp_HSequenceOfPnt pSeq1;
    TColgp_HSequenceOfPnt pSeq2;
    Standard_Integer NbPoints = 15;
    Standard_Real param;
	gp_Pnt p;

    GeomAdaptor_Curve C (bezierCurve1);
    GCPnts_UniformAbscissa myAlgo1(C, NbPoints);
    myAlgo1.Initialize (C, NbPoints);
    if (myAlgo1.IsDone())
    {
		Standard_Integer nbr = myAlgo1.NbPoints();
		for (Standard_Integer i = 1; i <= nbr; i++)
		{
			param = myAlgo1.Parameter(i);
			C.D0(param, p);
            pSeq1.Append(p);
		}
	}

    // Geting coordimates of points on bezierCurve2
    GeomAdaptor_Curve D (bezierCurve2);
    GCPnts_UniformAbscissa myAlgo2(D, NbPoints);
    myAlgo2.Initialize (D, NbPoints);
    if (myAlgo2.IsDone())
    {
		Standard_Integer nbr = myAlgo2.NbPoints();
		for (Standard_Integer i = 1; i <= nbr; i++)
		{
			param = myAlgo2.Parameter(i);
			D.D0(param, p);
			pSeq2.Append(p);
		}
	}

    for(Standard_Integer i = pSeq1.Length(); i > 0; i--)
    {
        gp_Pnt aPnt1 = pSeq1.Value(i);
        gp_Pnt aPnt2 = pSeq2.Value(i);

        Standard_Real theMajorRadius = aPnt1.X();
        Standard_Real theMinorRadius = aPnt2.Y();

        gp_Pnt coordEllips(0,0,aPnt1.Z());

        gp_Elips baseEllips(gp_Ax2(coordEllips,zDir),theMajorRadius,theMinorRadius);
        Handle(Geom_Ellipse) anEllips = new Geom_Ellipse(baseEllips);
        curveSeq1.Append( anEllips );
    }

    GeomFill_NSections fillOp(curveSeq1);
    fillOp.ComputeSurface();
    const Handle(Geom_BSplineSurface)& aSurf = fillOp.BSplineSurface();
    TopoDS_Shape shape = BRepBuilderAPI_MakeFace(aSurf, 0.001);

    // Building the Resulting Compound 
    TopoDS_Compound aResult;
    BRep_Builder aBuilder;
    aBuilder.MakeCompound (aResult);
    aBuilder.Add (aResult, shape);
    
    // Create a cylinder 
    Standard_Real X = 0, Y = -25, Z = 0; 
    gp_Ax2 axes = gp::ZOX(); 
    axes.Translate(gp_Vec(X,Y,Z)); 
	TopoDS_Shape aCylinder = BRepPrimAPI_MakeCylinder(axes,10.0,50.0, 90);

    // Cut the cylinder out from the shape
    BRepAlgoAPI_Cut cutMaker(aResult, aCylinder);
	TopoDS_Shape cutted = cutMaker.Shape();

    Standard_Real myThickness = -0.7;
    BRepOffsetAPI_MakeThickSolid aSolidMaker;
    aSolidMaker.MakeThickSolidBySimple(cutted, myThickness);
    TopoDS_Shape theSolid = aSolidMaker.Shape();

    //Write the model to a STL file
    std::cout << "Creating mesh..."  << std::flush;
    BRepMesh_IncrementalMesh meshMaker(theSolid, 0.01, Standard_False);
    meshMaker.Perform();

    try
    {
    StlAPI_Writer writer;
    writer.Write(theSolid, "model.stl");
    }catch(Standard_ConstructionError& e)
    {
        std::cout << e.GetMessageString() << std::endl;
    }
	std::cout << "Created model, file is written to model.stl" << std::endl;

    return 0;
}