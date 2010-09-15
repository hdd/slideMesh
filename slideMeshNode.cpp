//
// Copyright (C) 
// 
// File: slideMeshNode.cpp
//
// Dependency Graph Node: slideMesh
//
// Author: Maya Plug-in Wizard 2.0
//

#include "slideMeshNode.h"
#include <maya/M3dView.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MGlobal.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MItMeshVertex.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDagModifier.h>
#include <maya/MFnData.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatVector.h>
#include <maya/MIntArray.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItMeshFaceVertex.h>
#include <maya/MPointArray.h>
#include <maya/MDagPath.h>
#include <stdlib.h>
/*
 ID TO BE CHANGED !
 */

MTypeId     slideMesh::id( 0x80014 );
MObject     slideMesh::tolerance;    
MObject     slideMesh::maxParam;    
MObject     slideMesh::srcGeom;
MObject     slideMesh::dotN;

MObject     slideMesh::inDeformedMatrix;
MObject     slideMesh::inDeformerMatrix;

slideMesh::slideMesh() {
    system("clear");
}
slideMesh::~slideMesh() {


}

MStatus slideMesh::compute ( const MPlug& plug, MDataBlock& data )
{
                
		MStatus returnStatus;
		// get the input corresponding to this output
		//
		unsigned int index = plug.logicalIndex();
		MObject thisNode = this->thisMObject();
		MPlug inPlug(thisNode,input);
		inPlug.selectAncestorLogicalIndex(index,input);
		MDataHandle hInput = data.inputValue(inPlug);
		// get the input geometry and input groupId
		//
		MDataHandle inH = hInput.child(inputGeom);
		
		MDataHandle hGroup = hInput.child(groupId);
		
		unsigned int groupId = hGroup.asLong();
                
		MDataHandle hOutput = data.outputValue(plug);
		hOutput.copy(inH);
	
	
		MDataHandle srcH = data.inputValue(srcGeom, &returnStatus);

		MDataHandle tolH = data.inputValue(tolerance, &returnStatus);
		MDataHandle maxpH = data.inputValue(maxParam, &returnStatus);
		MDataHandle dotnH = data.inputValue(dotN, &returnStatus);
		
		MDataHandle MatrixDdHandle = data.inputValue(inDeformedMatrix, &returnStatus);
		MDataHandle MatrixDrHandle = data.inputValue(inDeformerMatrix, &returnStatus);

		MMatrix DdMatrix = MatrixDdHandle.asMatrix();
                MMatrix DrMatrix = MatrixDrHandle.asMatrix();

                MObject mI=inH.asMesh();
                MObject mO=hOutput.asMesh();
                MObject mS=srcH.asMesh();

                float toll=tolH.asFloat();
                float maxp=maxpH.asFloat();
                float dotn=dotnH.asFloat();
                
                MFnMesh meshFnI(mO);
                MFnMesh meshFnS(mS);


                MFloatPointArray Pts ;
                MFloatVectorArray NN ;

                MItMeshVertex vertIter( mO, NULL);

                for ( ; !vertIter.isDone(); vertIter.next() ) {

                      MFloatPoint pnt;
                      MPoint tmpp= vertIter.position( MSpace::kWorld );

                      pnt.x=tmpp.x;
                      pnt.y=tmpp.y;
                      pnt.z=tmpp.z;
                      
                      Pts.append (pnt) ;

                      MVector pntNormal ;

                      vertIter.getNormal (pntNormal, MSpace::kWorld );

                      MFloatVector vNormal (pntNormal) ;

                      NN.append (vNormal) ;

                }
		// recupero gli id dei vertici dell'idGroup
		MIntArray Vertex;

               
		MItGeometry iter(hOutput,groupId,true);
			for ( ; !iter.isDone(); iter.next()) {
				Vertex.append(iter.index());
			}
                
                
                MIntArray triIds;
                MPointArray trisP;
                MDagPath mdp;
                MDagPath::getAPathTo(mO,mdp);
                
                MItMeshPolygon pIter(mdp);
                
                pIter.getTriangles(trisP,triIds);
                
                
                MIntArray faceIds;
                MItMeshFaceVertex fIter(mdp);
			for ( ; !fIter.isDone(); fIter.next()) {
				faceIds.append(fIter.faceId());
			}
                
                MMeshIsectAccelParams param= meshFnS.autoUniformGridParams();
                

                MVector tmpNormal;

                for(unsigned i=0;i<Vertex.length();i++){
                    //cout << "------------------------------------------------------------"<< endl;
                    //cout << "\t\t\tVTX ID:\t "<< i << "\n"<< endl;
                    MFloatPoint P=Pts[Vertex[i]];
                    //cout << "P:\t" << P.x << "\t" << P.y  << "\t" << P.z << endl;        
                                MPoint tmpP =  MPoint(P.x,P.y,P.z,P.w)*DdMatrix;
                                //cout << "tmpP:\t" << tmpP.x << "\t" << tmpP.y  << "\t" << tmpP.z << endl;
                                P.x = tmpP.x;
                                P.y = tmpP.y;
                                P.z = tmpP.z;

                    // NORMALE
                    MFloatVector N=NN[Vertex[i]];
                    //cout << "N:\t" << N.x << "\t" << N.y  << "\t" << N.z << endl;

                                MVector tmpN =  MVector(N.x,N.y,N.z)*DdMatrix;
                                //cout << "tmpN:\t" << tmpN.x << "\t" << tmpN.y  << "\t" << tmpN.z << endl;

                                N.x = tmpN.x;
                                N.y = tmpN.y;
                                N.z = tmpN.z;

                    // HITPOINTS
                    MFloatPoint fpts;
                    
                    // DEFAULT VALUEs
                    int hitFace;

                    
                    bool hit = meshFnS.closestIntersection(P,N,NULL,NULL ,false,MSpace::kWorld,maxp,false,&param,fpts,NULL,&hitFace,NULL,NULL,NULL,toll);
                    
                    if((hit)){ 
                    meshFnS.getPolygonNormal(hitFace,tmpNormal,MSpace::kObject);
                    

                    double dot = MVector(N.x,N.y,N.z).angle(tmpNormal*DrMatrix);

                    if(dot>dotn){

                        MFloatPoint p = fpts;
                        MPoint pp(p[0],p[1],p[2]);
                        
                        meshFnI.setPoint(i,pp*DdMatrix.inverse());
                                        //Pts.set(pp,i);
			}
                }
			
            
        }
        hOutput.set(mO);

        data.setClean(plug);
	return MS::kSuccess;
}

void* slideMesh::creator()
{
	return new slideMesh();
}


MStatus slideMesh::initialize()
{
        
        MFnTypedAttribute tAttr;
        MFnNumericAttribute nAttr;

        MStatus	stat;  

        srcGeom = tAttr.create( "srcGeom", "srcG", MFnData::kMesh);    
        addAttribute(srcGeom);
        tAttr.setStorable(true);  
        attributeAffects( slideMesh::srcGeom, slideMesh::outputGeom );

        dotN=nAttr.create("dot","dn",MFnNumericData::kFloat,0.0) ;
        addAttribute(dotN);
        nAttr.setStorable(true);  
        nAttr.setKeyable(true);  
        attributeAffects( slideMesh::dotN, slideMesh::outputGeom );
        
        
        tolerance=nAttr.create("tolerance","tol",MFnNumericData::kFloat,1e-6) ;
        addAttribute(tolerance);
        nAttr.setStorable(true);  
        nAttr.setKeyable(true);  
        attributeAffects( slideMesh::tolerance, slideMesh::outputGeom );

        maxParam=nAttr.create("maxParam","maxp",MFnNumericData::kFloat,999.0) ;
        addAttribute(maxParam);
        nAttr.setStorable(true);   
        nAttr.setKeyable(true);  
        attributeAffects( slideMesh::maxParam, slideMesh::outputGeom );

        MFnMatrixAttribute mAttr;

        inDeformedMatrix = mAttr.create("inDefomedMatrix","inDdMtx",MFnMatrixAttribute::kDouble,&stat);
        mAttr.setStorable(true);
        addAttribute(inDeformedMatrix);

        inDeformerMatrix = mAttr.create("inDefomerMatrix","inDrMtx",MFnMatrixAttribute::kDouble,&stat);
        mAttr.setStorable(true);
        addAttribute(inDeformerMatrix);
        
        // ADDATTR
        attributeAffects( slideMesh::srcGeom, slideMesh::outputGeom );
        attributeAffects( slideMesh::inDeformedMatrix, slideMesh::outputGeom );
        attributeAffects( slideMesh::inDeformerMatrix, slideMesh::outputGeom );
        //attributeAffects( slideMesh::inputGeom, slideMesh::outputGeom );
        attributeAffects( slideMesh::maxParam, slideMesh::outputGeom );
        attributeAffects( slideMesh::tolerance, slideMesh::outputGeom );
		
        
	return MS::kSuccess;
}
