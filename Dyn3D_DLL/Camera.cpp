#include "stdafx.h"
#include "Camera.h"

Camera::Camera(float fov, float zoom) : fov(fov), zoom(zoom),
scalar(fov * zoom) {}

Camera::Camera(float fov, float zoom, Vertex& location,
			   Vertex& orientation, ObjectSpace* containerSpace)
	: ObjectSpace(location, orientation, containerSpace), fov(fov), zoom(zoom),
	scalar(fov * zoom) {}

__int8 TriangleCompare(Triangle& t1, Triangle& t2) {
	if (t1.z() > t2.z())
		return 1;
	return 0;
}

void Camera::perspecitve(ObjectSpace& objs, TriangleSet& triangles,
						 VertexSet& vertexes) {
	Transformation camtrans = getWorldTransformation().invert();
	std::vector<ObjectSpace*>& objsArray = objs.GetAll();
	for each(Object3D* o in objsArray) {
		Transformation& trans = o->getWorldTransformation();
		for each (Vertex* v in o->getVertexs())
			v->operator*=(trans).operator*=(camtrans);
		for each (Triangle* t in o->getTriangles())
			if (t->x()->z() > 0 || t->y()->z() > 0 || t->z()->z() > 0) {
				triangles.insert(t);
				vertexes.insert(t->x());
				vertexes.insert(t->y());
				vertexes.insert(t->z());
			}
	}
	for each (Vertex* v in vertexes) {
		const float f = scalar / v->z();
		v->x() *= f;
		v->y() *= f;
	}
}

void Camera::cropView(TriangleSet& triangles, VertexSet& vertexes,
					  const unsigned __int32& q_width,
					  const unsigned __int32& q_height) {
	for each (Triangle* t in triangles)
		if (((t->x()->x() > q_width && t->x()->x() < 0)
			&& (t->x()->y() > q_height && t->x()->y() < 0))
			|| ((t->y()->x() > q_width && t->y()->x() < 0)
			&& (t->y()->y() > q_height && t->y()->y() < 0))
			|| ((t->z()->x() > q_width && t->z()->x() < 0)
			&& (t->z()->y() > q_height && t->z()->y() < 0))) {
			triangles.erase(t);
		}
}

void Camera::setFOV(float & f) {
	fov = f;
	scalar = fov*zoom;
}

void Camera::setZoom(float & f) {
	zoom = f;
	scalar = fov*zoom;
}

void Camera::Handle_GetAll(std::vector<ObjectSpace*>& getArray) {
	__raise __GetAll(getArray);
}
