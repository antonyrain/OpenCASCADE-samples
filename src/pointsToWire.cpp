#include "TopoDS_Wire.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Vertex.hxx"
#include "BRepBuilderAPI_MakeVertex.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"

int main(int argc, char *argv[])
{
    gp_Pnt aPnt1(0,0,10);
    gp_Pnt aPnt2(0,0,20);
    //
    gp_Pnt aPnt3(0,10,0);
    gp_Pnt aPnt4(0,20,0);
    
    TopoDS_Vertex V1 = BRepBuilderAPI_MakeVertex(aPnt1);
    TopoDS_Vertex V2 = BRepBuilderAPI_MakeVertex(aPnt2);
    //
    TopoDS_Vertex V3 = BRepBuilderAPI_MakeVertex(aPnt3);
    TopoDS_Vertex V4 = BRepBuilderAPI_MakeVertex(aPnt4);
    
    TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(V1,V2);
    TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(V3,V4);

    TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2);
    
    return 0;
}