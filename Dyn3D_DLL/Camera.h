#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Object3D.h"

class Camera : public ObjectSpace {
public:
	Camera(float fov, float zoom);
	Camera(float fov, float zoom, Vertex& location,
		   Vertex& orientation, ObjectSpace* containerSpace);
	void perspecitve(ObjectSpace& objs, TriangleSet& triangles,
					 VertexSet& vertexes);
	void cropView(TriangleSet& triangles, VertexSet& vertexes,
				  const unsigned __int32& q_width, 
				  const unsigned __int32& q_height);
	void setFOV(float& f);
	void setZoom(float& f);
private:
	/*
	This event handler is fired when it's hooked container space's __GetAll
	event is fired.*/
	virtual void Handle_GetAll(std::vector<ObjectSpace*>& getArray);
	float fov, zoom, scalar;
};

#endif // !CAMERA_H

