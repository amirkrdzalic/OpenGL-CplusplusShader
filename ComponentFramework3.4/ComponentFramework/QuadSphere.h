/// A simple subdivided cube - SSF
#include "Vector.h"

using namespace MATH;
namespace GAME {


class QuadSphere{
private:
	int numVertices;
	int index;
	Vec4 *vertex;
	Vec4 *normals;
	Vec2 *texCoords;
	
public:
	QuadSphere(int numSubDivisions);
	~QuadSphere();

	inline int getNumVertices() { return numVertices; }
	inline Vec4* getVerticies() { return vertex; } 
	inline Vec4* getNormals() { return normals; } 
	inline Vec2* getTexCoords() { return texCoords; } 
	
	/// Delete these possible default constructors and operators 

	QuadSphere(const QuadSphere&) = delete;
	QuadSphere(QuadSphere &&) = delete;
	QuadSphere& operator=(const QuadSphere &) = delete;
	QuadSphere& operator=(QuadSphere &&) = delete;

	

protected:
	void loadFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d);
	void divideFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int count);
	void sphericalNormals();
};


}
