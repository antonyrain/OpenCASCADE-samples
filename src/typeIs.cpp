#include <iostream>
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"
#include "TopoDS_Edge.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeVertex.hxx"

using namespace std;

int main(int argc, char *argv[])
{
    gp_Pnt aPnt1(0,0,10);
    gp_Pnt aPnt2(0,0,20);
    TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(aPnt1);
    TopoDS_Vertex V2 = BRepBuilderAPI_MakeVertex(aPnt2);
    TopoDS_Edge anEdge = BRepBuilderAPI_MakeEdge(V1,V2);
    //
    TopAbs_ShapeEnum type = anEdge .ShapeType();

    switch (type)
    {
    case 0:
        cout << "Type is number: " << type << "TopAbs_COMPOUND" << endl;
        break;
    case 1:
        cout << "Type is number: " << type << "TopAbs_COMPSOLID" << endl;
        break;
    case 2:
        cout << "Type is number: " << type << "TopAbs_SOLID" << endl;
        break;
    case 3:
        cout << "Type is " << type << " - TopAbs_SHELL" << endl;
        break;
    case 4:
        cout << "Type is " << type << " - TopAbs_FACE" << endl;
        break;
    case 5:
        cout << "Type is " << type << " - TopAbs_WIRE" << endl;
        break;
    case 6:
        cout << "Type is " << type << " - TopAbs_EDGE" << endl;
        break;
    case 7:
        cout << "Type is " << type << " - TopAbs_VERTEX" << endl;
        break;
    case 8:
        cout << "Type is " << type << " - TopAbs_SHAPE" << endl;
        break;
    }
    
    return 0;
}

// enum TopAbs_ShapeEnum:
//
// TopAbs_COMPOUND = 0
// TopAbs_COMPSOLID = 1
// TopAbs_SOLID = 2
// TopAbs_SHELL = 3
// TopAbs_FACE = 4
// TopAbs_WIRE = 5
// TopAbs_EDGE = 6
// TopAbs_VERTEX = 7
// TopAbs_SHAPE = 8