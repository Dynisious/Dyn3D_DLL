#pragma once

#ifndef OBJECTSPACE_H
#define OBJECTSPACE_H

#include "stdafx.h"
#include "Point.h"
#include "Triangles_Vertexes.h"
#include <vector>

using namespace Triangles_Vertexes;

class ObjectSpace {
public:
	Vertex location, orientation;
	typedef Matrix<float, 4, 4> Transformation;

	ObjectSpace();
	ObjectSpace(Vertex& location, Vertex& orientation);
	ObjectSpace(Vertex& location, Vertex& orientation, ObjectSpace* containerSpace);
	ObjectSpace(const ObjectSpace& orig);
	virtual ~ObjectSpace();
	/*
	Creates a Transformation matrix using this location and orientation value
	inside the space.*/
	static Transformation& TransformationMatrix(Vertex& location, Vertex& orientation);
	/*
	Returns the transformation Matrix needed to transform objects inside this
	space into this ObjectSpace's space.*/
	Transformation& getTransformation();
	/*
	Returns the transformation Matrix needed to transform objects inside this
	space into world space.*/
	Transformation& getWorldTransformation();
	/*
	Returns an unhooked copy of this ObjectSpace without any hooked
	ObjectSpaces beneath it.*/
	virtual ObjectSpace& CopyMe();
	/*
	Returns an unhooked copy of this ObjectSpace with hooked copies of all
	ObjectSpaces beneath this one.*/
	ObjectSpace& CopyAll();
	/*
	Returns an array of pointers to this ObjectSpace and all ObjectSpaces below
	it. 'count' Will be equal to the length of the returned array.*/
	std::vector<ObjectSpace*>& GetAll();
	ObjectSpace* getContainerSpace();
protected:
	ObjectSpace* containerSpace;

	/*
	Unhookes this ObjectSpace from any container space and then hooks it to the
	passed ObjectSpace.*/
	virtual void hook(ObjectSpace* space);
	/*
	Unhooks this ObjectSpace from it's containerSpace.*/
	virtual void unhook();
	/*
	This is an event handler, fired when this ObjectSpace's container space
	gets destroyed.*/
	virtual void Handle_ContainerDestruction();

	__event void __Destruction();
	__event void __CopyAll(ObjectSpace* container);
	__event void __GetAll(std::vector<ObjectSpace*>& getArray);

	/*
	This event handler is fired when it's hooked container space's __CopyAll
	event is fired.*/
	virtual void Handle_CopyAll(ObjectSpace* container);
	/*
	This event handler is fired when it's hooked container space's __GetAll
	event is fired.*/
	virtual void Handle_GetAll(std::vector<ObjectSpace*>& getArray);
};

#endif // !OBJECTSPACE_H
