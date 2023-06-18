#include <vector>

using namespace std;

float colred = 1.0f;

void Gen_Triangle(vector<float>& vert, float ax, float ay, float bx, float by, float cx, float cy) {
	vert.push_back(ax);
	vert.push_back(ay);
	vert.push_back(0.0f);

	vert.push_back(0.0f);
	vert.push_back(0.0f);
	vert.push_back(0.0f);

	vert.push_back(bx);
	vert.push_back(by);
	vert.push_back(0.0f);

	vert.push_back(0.0f);
	vert.push_back(0.0f);
	vert.push_back(0.0f);

	vert.push_back(cx);
	vert.push_back(cy);
	vert.push_back(0.0f);

	vert.push_back(0.0f);
	vert.push_back(0.0f);
	vert.push_back(0.0f);
}

void Gen_Quad(vector<float>& vert, float posx, float posy, float width, float height) {
	Gen_Triangle(vert, posx, posy, posx + width, posy, posx + width, posy + height);
	Gen_Triangle(vert, posx, posy, posx, posy + height, posx + width, posy + height);
}

void Gen_3dtriangle(vector <float>& vert,
	float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz) {

	vert.push_back(ax);
	vert.push_back(ay);
	vert.push_back(az);

	vert.push_back(bx);
	vert.push_back(1.0f / 456.0f);
	vert.push_back(1.0f);

	vert.push_back(bx);
	vert.push_back(by);
	vert.push_back(bz);

	vert.push_back(bx);
	vert.push_back(1.0f / 456.0f);
	vert.push_back(1.0f);

	vert.push_back(cx);
	vert.push_back(cy);
	vert.push_back(cz);

	vert.push_back(bx);
	vert.push_back(1.0f / 456.0f);
	vert.push_back(1.0f);
}
// a = top left, b = top right, c = bottom left, d = bottom right
void Gen_3dquad(vector <float>& vert,
	float ax, float ay, float az,
	float bx, float by, float bz,
	float cx, float cy, float cz,
	float dx, float dy, float dz) {

	Gen_3dtriangle(vert, ax, ay, az, bx, by, bz, cx, cy, cz);
	Gen_3dtriangle(vert, bx, by, bz, cx, cy, cz, dx, dy, dz);
}

//circles
vector<float> Ngonxz(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	vector<float> vect;
	vect.push_back(((spx - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spz - cz)) + cx);
	vect.push_back(cy);
	vect.push_back(((spz - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spx - cx)) + cz);
	return vect;
}

vector<float> Ngonyz(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	vector<float> vect;
	vect.push_back(cx);
	vect.push_back(((spy - cy) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spz - cz)) + cy);
	vect.push_back(((spz - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spy - cy)) + cz);
	return vect;
}

vector<float> Ngonxy(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	vector<float> vect;
	vect.push_back(((spx - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spy - cy)) + cx);
	vect.push_back(((spy - cy) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spx - cx)) + cy);
	vect.push_back(cz);
	return vect;
}

//ovals 
vector<float> Ngonxy(float cx, float cy, float cz, float spxa, float spya, float spza, float spxb, float spyb, float spzb, float deg, int itr) {
	vector<float> vect;
	vect.push_back(((spxa - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spya - cy)) + cx);
	vect.push_back(((spyb - cy) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spxb - cx)) + cy);
	vect.push_back(cz);
	return vect;
}

vector<float> Ngonxz(float cx, float cy, float cz, float spxa, float spya, float spza, float spxb, float spyb, float spzb, float deg, int itr) {
	vector<float> vect;
	vect.push_back(((spxa - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spza - cz)) + cx);
	vect.push_back(cy);
	vect.push_back(((spzb - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spxb - cx)) + cz);
	return vect;
}

vector<float> Ngonyz(float cx, float cy, float cz, float spxa, float spya, float spza, float spxb, float spyb, float spzb, float deg, int itr) {
	vector<float> vect;
	vect.push_back(cx);
	vect.push_back(((spya - cy) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spza - cz)) + cy);
	vect.push_back(((spzb - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spyb - cy)) + cz);
	return vect;
}