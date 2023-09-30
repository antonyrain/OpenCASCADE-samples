# Makefile -- makefile tells make how to compile and link a program.

SOURCE_FILE		:= ./src/bottleTutorial.cpp
OUT_FILE		:= -o./bin/a.out
INCLUDE_PATH		:= -I/usr/local/Cellar/opencascade/7.7.2_1/include/opencascade
LIB_PATH		:= -L/usr/local/Cellar/opencascade/7.7.2_1/lib
COMPILER		:= clang++
VERSION			:= -std=c++14
EXECUTE			:= ./bin/a.out

# Opencascade libraries
LIB_FLAGS		:= -lTKernel -lTKStep -lTKMath -lTKG2d -lTKBin -lTKBinL -lTKBinTObj 
LIB_FLAGS		+= -lTKBinXCAF -lTKBO -lTKBool -lTKBRep -lTKCAF -lTKCDF -lTKDCAF 
LIB_FLAGS		+= -lTKDraw -lTKFeat -lTKFillet -lTKG3d -lTKGeomAlgo -lTKGeomBase 
LIB_FLAGS		+= -lTKHLR -lTKIGES -lTKLCAF -lTKMesh -lTKMeshVS -lTKOffset -lTKOpenGl 
LIB_FLAGS		+= -lTKPrim -lTKQADraw -lTKRWMesh -lTKService -lTKShHealing -lTKStd 
LIB_FLAGS		+= -lTKStdL -lTKSTEP209 -lTKSTEP -lTKSTEPAttr -lTKSTEPBase -lTKSTL 
LIB_FLAGS		+= -lTKTObj -lTKTObjDRAW -lTKTopAlgo -lTKTopTest -lTKV3d -lTKVCAF 
LIB_FLAGS		+= -lTKViewerTest -lTKVRML -lTKXCAF -lTKXDEDRAW -lTKXDEIGES -lTKXDESTEP 
LIB_FLAGS		+= -lTKXMesh -lTKXml -lTKXmlL -lTKXmlTObj -lTKXmlXCAF -lTKXSBase -lTKXSDRAW 

make:
	$(COMPILER) $(VERSION) $(SOURCE_FILE) $(OUT_FILE) $(INCLUDE_PATH) $(LIB_PATH) $(LIB_FLAGS)
out:
	$(EXECUTE)
