#pragma once

#ifndef TRIANGLES_VERTEXES_H
#define TRIANGLES_VERTEXES_H

#include "stdafx.h"
#include "Point.h"
#include "PointerSet.h"

namespace Triangles_Vertexes {
	typedef Point<float> Vertex;
	typedef Point<Vertex*> Triangle;
	typedef PointerSet::_PS<Triangle>::Set TriangleSet;
	typedef PointerSet::_PS<Vertex>::Set VertexSet;
};

#endif // !TRIANGLES_VERTEXES_H
