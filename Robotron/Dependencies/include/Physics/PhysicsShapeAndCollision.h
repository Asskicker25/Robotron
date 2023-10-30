#pragma once

#include <glm/glm.hpp>

enum PhysicsShape
{
	SPHERE,
	PLANE,
	TRIANGLE,
	AABB,
	CAPSULE,
	MESH_OF_TRIANGLES,
};

enum PhysicsMode
{
	STATIC,
	DYNAMIC,
	KINEMATIC,
};

enum CollisionMode
{
	TRIGGER,
	SOLID
};

struct iShape
{
	virtual ~iShape() {}

};

struct Aabb : public iShape
{
	Aabb() {}
	Aabb(glm::vec3 min, glm::vec3 max)
	{
		this->min = min;
		this->max = max;
	}
	glm::vec3 min;
	glm::vec3 max;
};

struct Sphere : public iShape
{
	Sphere() {}
	Sphere(glm::vec3 position, float radius)
	{
		this->position = position;
		this->radius = radius;
	}

	glm::vec3 position;
	float radius;
};

struct Triangle : public iShape
{
	Triangle() {}
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normal)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
		this->normal = normal;
	}

	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 normal;
};
struct Plane : iShape
{
	Plane() {}
	Plane(glm::vec3 normal, float dotofPoint)
	{
		this->normal = normal;
		this->dotofPoint = dotofPoint;
	}
	glm::vec3 normal;
	float dotofPoint;
};

static Aabb CalculateAABB(const std::vector<Vertex>& vertices)
{
	if (vertices.size() == 0)
	{
		return Aabb{ glm::vec3(0.0f), glm::vec3(0.0f) };
	}

	glm::vec3 min = vertices[0].positions;
	glm::vec3 max = vertices[0].positions;

	for (const Vertex& vertex : vertices)
	{
		min.x = std::min(min.x, vertex.positions.x);
		min.y = std::min(min.y, vertex.positions.y);
		min.z = std::min(min.z, vertex.positions.z);

		max.x = std::max(max.x, vertex.positions.x);
		max.y = std::max(max.y, vertex.positions.y);
		max.z = std::max(max.z, vertex.positions.z);
	}

	return Aabb{ min, max };
}

//static Sphere CalculateSphere(const std::vector<Vertex>& vertices)
//{
//    if (vertices.empty()) {
//        return Sphere{ glm::vec3(0.0f), -1.0f };
//    }
//
//    // Initialize the min and max points.
//    glm::vec3 minPoint = vertices[0].positions;
//    glm::vec3 maxPoint = vertices[0].positions;
//
//    for (const Vertex& vertex : vertices) {
//        minPoint = glm::min(minPoint, vertex.positions);
//        maxPoint = glm::max(maxPoint, vertex.positions);
//    }
//
//    glm::vec3 center = 0.5f * (minPoint + maxPoint);
//
//    float radius = glm::length(maxPoint - center);
//
//    return Sphere{ center, radius };
//}
static bool CollisionAABBvsAABB(const Aabb& a, const Aabb& b)
{
	// Exit with no intersection if separated along an axis
	if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return false;
	if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return false;
	if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return false;

	// Overlapping on all axes means AABBs are intersecting
	return true;
}
static bool CollisionAABBvsAABB(const Aabb& a, const Aabb& b,
	std::vector<glm::vec3>& collisionPoint,
	std::vector<glm::vec3>& collisionNormal)
{
	// Exit with no intersection if separated along an axis
	if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return false;
	if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return false;
	if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return false;

	// Overlapping on all axes means AABBs are intersecting

	Aabb intersectionAABB;
	intersectionAABB.min = glm::max(a.min, b.min);
	intersectionAABB.max = glm::min(a.max, b.max);

	glm::vec3 collisionpt = (intersectionAABB.min + intersectionAABB.max) * 0.5f;
	collisionPoint.push_back(collisionpt);

	glm::vec3 collisionNr = collisionpt - (a.min + a.max) * 0.5f;
	collisionNr = glm::normalize(collisionNr);

	/*std::cout << "Normal :" << collisionNr.x <<",";
	std::cout << "Normal :" << collisionNr.y <<",";
	std::cout << "Normal :" << collisionNr.z << std::endl;*/

	collisionNormal.push_back(collisionNr);

	return true;
}


// Computes the square distance between a point p and an AABB b
static float SqDistPointAABB(glm::vec3 p, Aabb b)
{
	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		// For each axis count any excess distance outside box extents
		float v = p[i];
		if (v < b.min[i])
			sqDist += (b.min[i] - v) * (b.min[i] - v);
		if (v > b.max[i])
			sqDist += (v - b.max[i]) * (v - b.max[i]);
	}
	return sqDist;
}
static const glm::vec3& ClosestPtPointAABB(glm::vec3 p, Aabb b)
{
	glm::vec3 q;
	for (int i = 0; i < 3; i++) {
		float v = p[i];
		if (v < b.min[i]) v = b.min[i]; // v = max(v, b.min[i])
		if (v > b.max[i]) v = b.max[i]; // v = min(v, b.max[i])
		q[i] = v;
	}
	return q;
}

static bool CollisionSpherevsAABB(Sphere* sphere, const Aabb& aabb, bool isSphere,
	std::vector<glm::vec3>& collisionPoint,
	std::vector<glm::vec3>& collisionNormal)
{
	// Compute squared distance between sphere center and AABB
	float sqDist = SqDistPointAABB(sphere->position, aabb);
	float sqRadius = sphere->radius * sphere->radius;

	if (sqDist <= sqRadius)
	{
		glm::vec3 collisionPt = ClosestPtPointAABB(sphere->position, aabb);

		glm::vec3 collisonNr = glm::vec3(0.0f);

		if (isSphere)
		{
			collisonNr = collisionPt - sphere->position;
		}
		else
		{
			collisonNr = collisionPt - ((aabb.min + aabb.max) * 0.5f);
			collisonNr = glm::normalize(collisonNr);
		}

		collisionPoint.push_back(collisionPt);
		collisionNormal.push_back(collisonNr);

		return true;
	}

	return false;
}

static bool CollisionSphereVSSphere(Sphere* sphere1, Sphere* sphere2,
	std::vector<glm::vec3>& collisionPoint,
	std::vector<glm::vec3>& collisionNormal)
{

	glm::vec3 collisionPt = glm::vec3(1.0f);
	glm::vec3 collisionNr = glm::vec3(1.0f);

	glm::vec3 d = sphere2->position - sphere1->position;
	float dist2 = glm::dot(d, d);

	float radiusSum = sphere1->radius + sphere2->radius;
	float radius2 = radiusSum * radiusSum;

	if (dist2 <= radius2)
	{
		if (dist2 != 0)
		{
			collisionNr = glm::normalize(d);
		}
		else
		{
			collisionNr = glm::normalize(glm::vec3(1.0f));
		}

		collisionPt = sphere1->position + sphere1->radius * collisionNr;

		collisionPoint.push_back(collisionPt);
		collisionNormal.push_back(collisionNr);

		//Debugger::Print("Collision");

		return true;
	}

	return false;
}

static glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
	float snom = glm::dot(p - a, ab), sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
	float tnom = glm::dot(p - a, ac), tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
	float unom = glm::dot(p - b, bc), udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
	glm::vec3 n = glm::cross(b - a, c - a);
	float vc = glm::dot(n, glm::cross(a - p, b - p));
	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
	float va = glm::dot(n, glm::cross(b - p, c - p));
	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
	float vb = glm::dot(n, glm::cross(c - p, a - p));
	// If P outside CA and within feature region of CA,
	// return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}
static glm::vec3 ClosestPtPlaneToAABB(const Plane& plane, const Aabb& aabb) 
{
	// Calculate the signed distance from the AABB center to the plane
	glm::vec3 aabbCenter = 0.5f * (aabb.min + aabb.max);
	float distance = glm::dot(plane.normal, aabbCenter) - plane.dotofPoint;

	// Calculate the closest point by projecting the center of the AABB onto the plane
	glm::vec3 closestPoint = aabbCenter - distance * plane.normal;

	// Clamp the closest point to the extents of the AABB
	for (int i = 0; i < 3; i++) {
		closestPoint[i] = std::max(aabb.min[i], std::min(closestPoint[i], aabb.max[i]));
	}

	return closestPoint;
}

static glm::vec3 ClosestPtTriangleToAABB(const Aabb& aabb, const Triangle& triangle)
{
	// Calculate collision point using barycentric coordinates
	glm::vec3 aabbCenter = 0.5f * (aabb.min + aabb.max);
	glm::vec3 intersectionPoint;

	glm::vec3 e1 = triangle.v2 - triangle.v1;
	glm::vec3 e2 = triangle.v3 - triangle.v1;
	glm::vec3 h = glm::cross(aabbCenter - triangle.v1, e2);
	float a = glm::dot(e1, h);

	float f = 1.0f / a;
	glm::vec3 s = aabbCenter - triangle.v1;
	float u = f * glm::dot(s, h);

	glm::vec3 q = glm::cross(s, e1);
	float v = f * glm::dot(aabbCenter - triangle.v1, q);

	float t = f * glm::dot(e2, q);
	intersectionPoint = triangle.v1 + u * e1 + v * e2;

	return intersectionPoint;
}

static bool CollisionSphereVsTriangle(Sphere* sphere, const Triangle& triangle, glm::vec3& collisionPoint)
{
	glm::vec3 v1ToSphere = sphere->position - triangle.v1;

	float distanceToPlane = glm::dot(v1ToSphere, triangle.normal);

	if (distanceToPlane < -sphere->radius) 
	{
		return false; 
	}

	glm::vec3 closestPointOnTriangle = ClosestPtPointTriangle(sphere->position, triangle.v1, triangle.v2, triangle.v3);

	glm::vec3 closestPointToSphere = closestPointOnTriangle - sphere->position;
	float distanceToClosest = glm::length(closestPointToSphere);

	if (distanceToClosest <= sphere->radius)
	{
		collisionPoint = closestPointOnTriangle;
		return true;  
	}
	return false; 
}

//static bool CollisionSphereVsTriangle(Sphere* sphere, const Triangle& triangle, glm::vec3& collisionPoint)
//{
//	collisionPoint = ClosestPtPointTriangle(sphere->position, triangle.v1, triangle.v2, triangle.v3);
//
//	glm::vec3 v = collisionPoint - sphere->position;
//	float squaredDistance = glm::dot(v, v);
//
//	return squaredDistance <= (sphere->radius * sphere->radius);
//}
static bool CollisionAABBVsPlane(const Plane& plane, const Aabb& aabb, glm::vec3& collisionPoint)
{

	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	glm::vec3 e = (aabb.max - aabb.min) * 0.5f; // Positive extents
	float r = glm::dot(e, glm::abs(plane.normal));

	// Compute the distance of the box center from the plane
	glm::vec3 c = 0.5f * (aabb.min + aabb.max); // AABB center
	float s = glm::dot(plane.normal, c) - plane.dotofPoint;

	// Intersection occurs when the distance s falls within [-r, +r] interval
	if (glm::abs(s) <= r)
	{

		collisionPoint = ClosestPtPlaneToAABB(plane, aabb);
		return true;
	}

	return false;
}

static bool CollisionAABBVsTriangle(const Aabb& aabb,const Triangle& triangle, glm::vec3& collisionPoint)
{
	for (int i = 0; i < 3; i++) 
	{
		glm::vec3 axis;
		if (i == 0) axis = glm::vec3(1.0f, 0.0f, 0.0f);
		else if (i == 1) axis = glm::vec3(0.0f, 1.0f, 0.0f);
		else axis = glm::vec3(0.0f, 0.0f, 1.0f);

		// Project AABB and Triangle onto the axis
		float aabbMin = glm::dot(aabb.min, axis);
		float aabbMax = glm::dot(aabb.max, axis);

		float triV1 = glm::dot(triangle.v1, axis);
		float triV2 = glm::dot(triangle.v2, axis);
		float triV3 = glm::dot(triangle.v3, axis);

		// Find the min and max values for the Triangle
		float triMin = glm::min(triV1, glm::min(triV2, triV3));
		float triMax = glm::max(triV1, glm::max(triV2, triV3));

		// Check for separation
		if (triMax < aabbMin || triMin > aabbMax) {
			// Separation along this axis, no collision
			return false;
		}
	}

	collisionPoint = ClosestPtTriangleToAABB(aabb, triangle);
	return true;
}

//static bool CollisionAABBVsTriangle(const Aabb& aabb,const Triangle& t, glm::vec3& collisionPoint)
//{
//	//Debugger::Print("AABB VS PLANE");
//
//	float p0, p1, p2, r;
//
//	Triangle triangle = t;
//
//	// Compute box center and extents (if not already given in that format)
//	glm::vec3 c = (aabb.min + aabb.max) * 0.5f;
//	float e0 = (aabb.max.x - aabb.min.x) * 0.5f;
//	float e1 = (aabb.max.y - aabb.min.y) * 0.5f;
//	float e2 = (aabb.max.z - aabb.min.z) * 0.5f;
//
//	// Translate triangle as conceptually moving AABB to origin
//	triangle.v1 -= c;
//	triangle.v2 -= c;
//	triangle.v3 -= c;
//
//	// Compute edge vectors for triangle
//	glm::vec3 f0 = triangle.v2 - triangle.v1, f1 = triangle.v3 - triangle.v2, f2 = triangle.v1 - triangle.v3;
//
//	// Test axes a00..a22 (category 3)
//	// Test axis a00
//	p0 = triangle.v1.z * triangle.v2.y - triangle.v1.y * triangle.v2.z;
//	p2 = triangle.v3.z * (triangle.v2.y - triangle.v1.y) - triangle.v3.z * (triangle.v2.z - triangle.v1.z);
//	r = e1 * glm::abs(f0.z) + e2 * glm::abs(f0.y);
//	if (glm::max(-glm::max(p0, p2), glm::min(p0, p2)) > r) return false; // Axis is a separating axis
//
//	// Repeat similar tests for remaining axes a01..a22
//	//...
//
//		// Test the three axes corresponding to the face normals of AABB b (category 1).
//		// Exit if...
//		// ... [-e0, e0] and [min(v0.x,v1.x,v2.x), max(v0.x,v1.x,v2.x)] do not overlap
//	if (glm::max(glm::max(triangle.v1.x, triangle.v2.x), triangle.v3.x) < -e0 || glm::min(glm::min(triangle.v1.x, triangle.v2.x), triangle.v3.x) > e0) return false;
//	// ... [-e1, e1] and [min(v0.y,v1.y,v2.y), max(v0.y,v1.y,v2.y)] do not overlap
//	if (glm::max(glm::max(triangle.v1.y, triangle.v2.y), triangle.v3.y) < -e1 || glm::min(glm::min(triangle.v1.y, triangle.v2.y), triangle.v3.y) > e1) return false;
//	// ... [-e2, e2] and [min(v0.z,v1.z,v2.z), max(v0.z,v1.z,v2.z)] do not overlap
//	if (glm::max(glm::max(triangle.v1.z, triangle.v2.z), triangle.v3.z) < -e2 || glm::min(glm::min(triangle.v1.z, triangle.v2.z), triangle.v3.z) > e2) return false;
//
//	// Test separating axis corresponding to triangle face normal (category 2)
//	Plane p;
//	p.normal = glm::cross(f0, f1);
//	p.dotofPoint = glm::dot(p.normal, triangle.v1);
//
//	if (CollisionAABBVsPlane(p, aabb, collisionPoint))
//	{
//		return true;
//	}
//
//	return false;
//}

static bool CollisionSphereVsMeshOfTriangles(Sphere* sphere,
	const glm::mat4& transformMatrix,
	const std::vector <std::vector <Triangle>>& triangles,
	const std::vector<std::vector<Sphere*>>& triangleSpheres,
	std::vector<glm::vec3>& collisionPoints,
	std::vector<glm::vec3>& collisionNormals)
{

	float maxScale = glm::max(glm::max(transformMatrix[0][0], transformMatrix[1][1]), transformMatrix[2][2]);

	collisionPoints.clear();
	Sphere* sphereTriangle = new Sphere();

	for (size_t i = 0; i < triangles.size(); i++)
	{
		const std::vector<Triangle>& triangleList = triangles[i];
		const std::vector<Sphere*>& sphereList = triangleSpheres[i];

		for (size_t j = 0; j < triangleList.size(); j++)
		{
			Triangle triangle = triangleList[j];

			// Transform the sphere's position using the transformMatrix
			glm::vec4 transformedCenter = transformMatrix * glm::vec4(sphereList[j]->position, 1.0f);
			sphereTriangle->position = glm::vec3(transformedCenter);

			// Transform the sphere's radius based on scaling
			sphereTriangle->radius = sphereList[j]->radius * maxScale;

			// Now you can check for collision between the transformed sphere and sphereTriangle
			std::vector<glm::vec3> collisionPoint;
			std::vector<glm::vec3> collisionNormal;
			if (CollisionSphereVSSphere(sphere, sphereTriangle, collisionPoint, collisionNormal))
			{
				glm::vec3 point = glm::vec3(0.0f);

				triangle.v1 = transformMatrix * glm::vec4(triangle.v1, 1.0f);
				triangle.v2 = transformMatrix * glm::vec4(triangle.v2, 1.0f);
				triangle.v3 = transformMatrix * glm::vec4(triangle.v3, 1.0f);

				if (CollisionSphereVsTriangle(sphere, triangle, point))
				{
					//Debugger::Print("Sphere vs Triangle");
					//glm::vec3 normal = point - sphere->position;

					glm::vec3 normal = transformMatrix * glm::vec4(triangle.normal,0.0f);

					collisionPoints.push_back(point);
					collisionNormals.push_back(normal);
				}
			}
		}
	}

	delete sphereTriangle;


	if (collisionPoints.size() > 0)
		return true;
	//std::cout << "Size : " << collisionPoints.size()<<std::endl;

	return false;
}

static bool CollisionAABBVsMeshOfTriangles(const Aabb& aabb,
	const glm::mat4& transformMatrix,
	const std::vector <std::vector <Triangle>>& triangles,
	const std::vector<std::vector<Sphere*>>& triangleSpheres,
	std::vector<glm::vec3>& collisionPoints,
	std::vector<glm::vec3>& collisionNormals)
{

	float maxScale = glm::max(glm::max(transformMatrix[0][0], transformMatrix[1][1]), transformMatrix[2][2]);

	collisionPoints.clear();
	Sphere* sphereTriangle = new Sphere();

	for (size_t i = 0; i < triangles.size(); i++)
	{
		const std::vector<Triangle>& triangleList = triangles[i];
		const std::vector<Sphere*>& sphereList = triangleSpheres[i];

		for (size_t j = 0; j < triangleList.size(); j++)
		{
			Triangle triangle = triangleList[j];

			// Transform the sphere's position using the transformMatrix
			glm::vec4 transformedCenter = transformMatrix * glm::vec4(sphereList[j]->position, 1.0f);
			sphereTriangle->position = glm::vec3(transformedCenter);

			// Transform the sphere's radius based on scaling
			sphereTriangle->radius = sphereList[j]->radius * maxScale;

			// Now you can check for collision between the transformed sphere and sphereTriangle
			std::vector<glm::vec3> collisionPoint;
			std::vector<glm::vec3> collisionNormal;


			if (CollisionSpherevsAABB(sphereTriangle, aabb, false, collisionPoint, collisionNormal))
			{
				//std::cout << "SphereVsAAB" << std::endl;
				glm::vec3 point = glm::vec3(0.0f);

				triangle.v1 = transformMatrix * glm::vec4(triangle.v1, 1.0f);
				triangle.v2 = transformMatrix * glm::vec4(triangle.v2, 1.0f);
				triangle.v3 = transformMatrix * glm::vec4(triangle.v3, 1.0f);

				if (CollisionAABBVsTriangle(aabb, triangle, point))
				{
					//std::cout << "TVsAAB" << std::endl;
					glm::vec3 normal = transformMatrix * glm::vec4(triangle.normal, 0.0f);

					collisionPoints.push_back(point);
					collisionNormals.push_back(normal);
				}
			}
		}
	}

	delete sphereTriangle;


	if (collisionPoints.size() > 0)
		return true;
	//std::cout << "Size : " << collisionPoints.size()<<std::endl;

	return false;
}

static bool RayCastAABB(const glm::vec3& rayOrigin, glm::vec3& rayDir,
	const Aabb& aabb, float rayDistance, glm::vec3& collisionPt, glm::vec3& collisionNormal) 
{
	rayDir = glm::normalize(rayDir);

	glm::vec3 invDir = 1.0f / rayDir;
	glm::vec3 tMin = (aabb.min - rayOrigin) * invDir;
	glm::vec3 tMax = (aabb.max - rayOrigin) * invDir;

	float tNear = glm::max(glm::max(glm::min(tMin.x, tMax.x), glm::min(tMin.y, tMax.y)), glm::min(tMin.z, tMax.z));
	float tFar = glm::min(glm::min(glm::max(tMin.x, tMax.x), glm::max(tMin.y, tMax.y)), glm::max(tMin.z, tMax.z));

	if (tNear > tFar || tFar < 0.0f || tNear > rayDistance) {
		return false; 
	}

	float t = tNear;
	collisionPt = rayOrigin + rayDir * t;


	if (tNear == tMin.y) {
		collisionNormal = glm::vec3(0, -1, 0);  // Bottom face
	}
	else if (tNear == tMax.y) {
		collisionNormal = glm::vec3(0, 1, 0);  // Top face
	}
	else {
		collisionNormal = glm::normalize(tNear == tMin.x ? glm::vec3(-1, 0, 0) : tNear == tMin.z ? glm::vec3(0, 0, -1) : glm::vec3(1, 0, 0));
	}

	return true;
}

static bool RayCastSphere(const glm::vec3& rayOrigin, glm::vec3& rayDir, 
	Sphere* sphere, float rayDistance, glm::vec3& collisionPt, glm::vec3& collisionNormal) 
{
	rayDir = glm::normalize(rayDir);

	glm::vec3 L = sphere->position - rayOrigin;
	float tca = glm::dot(L, rayDir);
	if (tca < 0.0f) 
	{
		return false;  
	}

	float d2 = glm::dot(L, L) - tca * tca;
	if (d2 > sphere->radius * sphere->radius)
	{
		return false;  
	}

	float thc = sqrt(sphere->radius * sphere->radius - d2);
	float t0 = tca - thc;
	float t1 = tca + thc;

	if (t0 > t1) 
	{
		std::swap(t0, t1);
	}

	if (t0 < 0.0f)
	{
		t0 = t1;  
		if (t0 < 0.0f || t0 > rayDistance) 
		{
			return false;  
		}
	}
	else if (t0 > rayDistance) {
		return false;  
	}

	collisionPt = rayOrigin + rayDir * t0;
	collisionNormal = glm::normalize(collisionPt - sphere->position);

	return true;
}

static bool RayCastTriangle(const glm::vec3& rayOrigin, glm::vec3& rayDirection, 
	const float& maxDistance, const Triangle& triangle,
	glm::vec3& collisionPt, glm::vec3& collisionNr) 
{
	rayDirection = glm::normalize(rayDirection);

	const float EPSILON = 0.000001f;

	glm::vec3 edge1, edge2, h, s, q;
	float a, f, u, v, t;

	edge1 = triangle.v2 - triangle.v1;
	edge2 = triangle.v3 - triangle.v1;

	h = glm::cross(rayDirection, edge2);
	a = glm::dot(edge1, h);

	if (a > -EPSILON && a < EPSILON) {
		return false; // Ray is parallel to the triangle
	}

	f = 1.0f / a;
	s = rayOrigin - triangle.v1;
	u = f * glm::dot(s, h);

	if (u < 0.0f || u > 1.0f) {
		return false;
	}

	q = glm::cross(s, edge1);
	v = f * glm::dot(rayDirection, q);

	if (v < 0.0f || u + v > 1.0f) {
		return false;
	}

	t = f * glm::dot(edge2, q);

	if (t > EPSILON && t <= maxDistance) 
	{
		collisionPt = rayOrigin + rayDirection * t;
		return true;
	}

	return false;
}

static bool RayCastMesh(const glm::vec3& rayOrigin, glm::vec3& rayDirection,
	const glm::mat4& transformMatrix, const float& maxDistance,
	const std::vector <std::vector <Triangle>>& triangles,
	glm::vec3& collisionPt, glm::vec3& collisionNr)
{
	rayDirection = glm::normalize(rayDirection);

	for (size_t i = 0; i < triangles.size(); i++)
	{
		const std::vector<Triangle>& triangleList = triangles[i];

		for (size_t j = 0; j < triangleList.size(); j++)
		{
			Triangle triangle = triangleList[j];
			triangle.v1 = transformMatrix * glm::vec4(triangle.v1, 1.0f);
			triangle.v2 = transformMatrix * glm::vec4(triangle.v2, 1.0f);
			triangle.v3 = transformMatrix * glm::vec4(triangle.v3, 1.0f);

			if (RayCastTriangle(rayOrigin, rayDirection, maxDistance, triangle, collisionPt, collisionNr))
			{
				collisionNr = transformMatrix * glm::vec4(triangle.normal, 0.0f);
				return true;
			}
		}
	}

	return false;
}