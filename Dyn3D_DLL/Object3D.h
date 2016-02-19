#pragma once

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include "ObjectSpace.h"
#include "Triangles_Vertexes.h"
#include "PointerSet.h"

/*
Object3Ds have an internal arrays of triangles and vertexes as well as a location and orientation.*/
class Object3D : public ObjectSpace {
public:
	Object3D(Vertex& location, Vertex& orientation,
			 TriangleSet& triangles);
	Object3D(Vertex& location, Vertex& orientation,
			 TriangleSet& triangles,
			 ObjectSpace*& containerSpace);
	Object3D(const Object3D& orig);
	virtual ~Object3D();
	/*
	Translates this Object3D by the passed amount.*/
	Object3D& Translation(Vertex& trans);
	/*
	Rotates this Object3D by the passed amount.*/
	Object3D& Rotation(Vertex& rotate);/*
	Returns an unhooked copy of this Object3D without any hooked
	ObjectSpaces beneath it.*/
	virtual Object3D& CopyMe();
	TriangleSet& getTriangles();
	VertexSet& getVertexs();
protected:
	/*
	This event handler is fired when it's hooked container space's __GetAll
	event is fired.*/
	virtual void Handle_GetAll(std::vector<ObjectSpace*>& getArray);
private:
	TriangleSet triangles;
	VertexSet vertexes;
};

#endif // !OBJECT3D_H
