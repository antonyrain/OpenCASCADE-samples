#include "STEPControl_Reader.hxx"
#include "StlAPI_Writer.hxx"
#include "TopoDS_Shape.hxx"
#include "Standard_ConstructionError.hxx"
#include "BRepMesh_IncrementalMesh.hxx"

int main(int argc, char *argv[])
{
    STEPControl_Reader reader;
    reader.ReadFile(argv[1]);
    reader.TransferRoots();
    TopoDS_Shape stepShape = reader.OneShape();

    std::cout << "Creating mesh..."  << std::flush;
    BRepMesh_IncrementalMesh meshMaker(stepShape, 0.01, Standard_False);
    meshMaker.Perform();

    try
    {
    StlAPI_Writer writer;
    writer.Write(stepShape,argv[2]);
    }
    catch(Standard_ConstructionError& e)
    {
        std::cout << e.GetMessageString() << std::endl;
    }

    std::cout << "Done" << std::endl;
    return 0;
}