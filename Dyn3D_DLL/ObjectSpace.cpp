#include "stdafx.h"
#include "ObjectSpace.h"
#include <ctgmath>

ObjectSpace::ObjectSpace()
	: location(Vertex()), orientation(Vertex()) {}

ObjectSpace::ObjectSpace(Vertex& location, Vertex& orientation)
	: location(location), orientation(orientation), containerSpace(0) {}

ObjectSpace::ObjectSpace(Vertex& location, Vertex& orientation,
						 ObjectSpace* containerSpace) : location(location),
	orientation(orientation), containerSpace(0) {
	hook(containerSpace);
}

ObjectSpace::ObjectSpace(const ObjectSpace& orig) : location(orig.location),
orientation(orig.orientation), containerSpace(0) {
	hook(orig.containerSpace);
}

ObjectSpace::~ObjectSpace() {
	unhook();
	__raise __Destruction();
}

ObjectSpace::Transformation& ObjectSpace::TransformationMatrix(Vertex& location,
												  Vertex& orientation) {
	Transformation& res = *new Transformation();
	res.set(0, 0, cos(orientation.x()) * cos(orientation.z()));
	res.set(0, 1, -cos(orientation.y()) * sin(orientation.z()));
	res.set(0, 2, sin(orientation.y()));
	res.set(1, 0, (cos(orientation.x()) * sin(orientation.z()))
			+ (sin(orientation.x()) * sin(orientation.y()) * cos(orientation.z())));
	res.set(1, 1, (cos(orientation.x()) * cos(orientation.z()))
			- (sin(orientation.x()) * sin(orientation.x()) * sin(orientation.z())));
	res.set(2, 0, sin(orientation.x()) * sin(orientation.z()));
	res.set(2, 1, sin(orientation.x()) * cos(orientation.z()));
	res.set(2, 2, cos(orientation.x()) * cos(orientation.y()));
	res.set(3, 0, location.x());
	res.set(3, 1, location.y());
	res.set(3, 2, location.z());
	return res;
}

ObjectSpace::Transformation& ObjectSpace::getTransformation() {
	return TransformationMatrix(location, orientation);
}

ObjectSpace::Transformation& ObjectSpace::getWorldTransformation() {
	ObjectSpace* space = containerSpace;
	Transformation& res = getTransformation();
	while (space) {
		res.set(3, 3, 1);
		res = res * space->getTransformation();
		space = space->containerSpace;
	}
	return res;
}

ObjectSpace& ObjectSpace::CopyMe() {
	ObjectSpace& res = *new ObjectSpace(*this);
	res.unhook();
	return res;
}

ObjectSpace& ObjectSpace::CopyAll() {
	ObjectSpace& res = CopyMe();
	__raise __CopyAll(&res);
	return res;
}

std::vector<ObjectSpace*>& ObjectSpace::GetAll() {
	std::vector<ObjectSpace*>& res = *new std::vector<ObjectSpace*>();
	res.push_back(this);
	__raise __GetAll(res);
	return res;
}

ObjectSpace* ObjectSpace::getContainerSpace() {
	return containerSpace;
}

void ObjectSpace::hook(ObjectSpace* space) {
	unhook();
	containerSpace = space;
	if (containerSpace) {
		__hook(&ObjectSpace::__Destruction, containerSpace, &ObjectSpace::unhook);
		__hook(&ObjectSpace::__Destruction, containerSpace, &ObjectSpace::Handle_ContainerDestruction);
		__hook(&ObjectSpace::__CopyAll, containerSpace, &ObjectSpace::Handle_CopyAll);
		__hook(&ObjectSpace::__GetAll, containerSpace, &ObjectSpace::Handle_GetAll);
	}
}

void ObjectSpace::unhook() {
	if (containerSpace) {
		__unhook(&ObjectSpace::__Destruction, containerSpace, &ObjectSpace::unhook);
		__unhook(&ObjectSpace::__Destruction, containerSpace, &ObjectSpace::Handle_ContainerDestruction);
		__unhook(&ObjectSpace::__CopyAll, containerSpace, &ObjectSpace::Handle_CopyAll);
		__unhook(&ObjectSpace::__GetAll, containerSpace, &ObjectSpace::Handle_GetAll);
	}
}

void ObjectSpace::Handle_ContainerDestruction() {}

void ObjectSpace::Handle_CopyAll(ObjectSpace* container) {
	ObjectSpace res = CopyMe();
	res.hook(container);
	__raise __CopyAll(&res);
}

void ObjectSpace::Handle_GetAll(std::vector<ObjectSpace*>& getArray) {}
