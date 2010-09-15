#ifndef _slideMeshNode
#define _slideMeshNode
//
// Copyright (C) 
// 
// File: slideMeshNode.h
//
// Dependency Graph Node: slideMesh
//
// Author: Maya Plug-in Wizard 2.0
//

#include <maya/MPxDeformerNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/M3dView.h>
#include <maya/MBoundingBox.h>
 
class slideMesh : public MPxDeformerNode
{
public:
	slideMesh();
	virtual	~slideMesh(); 

	virtual MStatus		compute ( const MPlug& plug, MDataBlock& data );
        
	static  void*		creator();
	static  MStatus		initialize();
        /*
        virtual void draw(	M3dView & view, const MDagPath & path,M3dView::DisplayStyle style,M3dView::DisplayStatus status );
	virtual bool isBounded() const ;
	virtual MBoundingBox boundingBox() const ;
        */
public:
    static		MTypeId			id;
    //static      MObject         inputGeom;
	//static      MObject         ouptutGeom;
    static      MObject         maxParam;
    static      MObject         tolerance;
    static      MObject         srcGeom;
    static      MObject         inDeformedMatrix;
    static      MObject         inDeformerMatrix;
    static      MObject         dotN;
};

#endif
