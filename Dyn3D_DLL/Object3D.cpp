#include "stdafx.h"
#include "Object3D.h"
#include <functional>

using namespace Triangles_Vertexes;

Object3D::Object3D(Vertex& location, Vertex& orientation,
				   TriangleSet& triangles)
	: ObjectSpace(location, orientation), triangles(TriangleSet()) {
	for each (Triangle* t in triangles) {
		t->x() = *vertexes.insert(t->x()).first;
		t->y() = *vertexes.insert(t->y()).first;
		t->z() = *vertexes.insert(t->z()).first;
	}
}

Object3D::Object3D(Vertex& location, Vertex& orientation,
				   TriangleSet& triangles, ObjectSpace*& containerSpace)
	: ObjectSpace(location, orientation, containerSpace),
	triangles(triangles) {
	for each (Triangle* t in triangles) {
		t->x() = *vertexes.insert(t->x()).first;
		t->y() = *vertexes.insert(t->y()).first;
		t->z() = *vertexes.insert(t->z()).first;
	}
}

Object3D::Object3D(const Object3D& orig) : ObjectSpace(orig),
triangles(orig.triangles), vertexes(orig.vertexes) {}

Object3D::~Object3D() {
	for each (Vertex* v in vertexes)
		delete v;
	for each (Triangle* t in triangles)
		delete t;
}

Object3D& Object3D::Translation(Vertex& trans) {
	location += trans;
	return *this;
}

Object3D& Object3D::Rotation(Vertex& rotate) {
	orientation += rotate;
	return *this;
}

Object3D& Object3D::CopyMe() {
	Object3D& res = *new Object3D(*this);
	res.unhook();
	return res;
}

TriangleSet& Object3D::getTriangles() {
	return triangles;
}

VertexSet& Object3D::getVertexs() {
	return vertexes;
}

void Object3D::Handle_GetAll(std::vector<ObjectSpace*>& getArray) {
	getArray.push_back(this);
}
