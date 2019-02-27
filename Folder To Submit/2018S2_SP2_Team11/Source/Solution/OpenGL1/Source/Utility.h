#ifndef UTILITY_H
#define UTILITY_H
#include "Vertex.h"
#include "Mtx44.h"

//operator overloading for position
Position operator*(const Mtx44 &lhs, const Position &rhs);

Vector3 TripleCrossProduct(Vector3 first, Vector3 sec, Vector3 third);

#endif

