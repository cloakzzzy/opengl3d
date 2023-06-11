#pragma once
#include <math.h>
#include "libs/glm/glm.hpp"
#include <vector>


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

	vert.push_back(bz);
	vert.push_back(1.0f / 456.0f);
	vert.push_back(1.0f);

	vert.push_back(bx);
	vert.push_back(by);
	vert.push_back(bz);

	vert.push_back(bz);
	vert.push_back(1.0f / 456.0f);
	vert.push_back(1.0f);

	vert.push_back(cx);
	vert.push_back(cy);
	vert.push_back(cz);

	vert.push_back(bz);
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

vector<float> Ngonxz(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	vector<float> vect;
	vect.push_back(((spx - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spz - cz)) + cx);
	vect.push_back(cy);
	vect.push_back(((spz - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spx - cx)) + cz);
	return vect;
}

vector<float> Ngonyz(float cx, float cy, float cz, float spx, float spy, float spz,float deg, int itr) {
	vector<float> vect;
	vect.push_back(cx);
	vect.push_back( ( (spy - cy) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spz - cz) )  + cy);
	vect.push_back( ( (spz - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spy - cy) )  + cz);
	return vect;
}

vector<float> Ngonxy(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	vector<float> vect;
	vect.push_back(((spx - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spy - cy)) + cx);
	vect.push_back(((spy - cy) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spx - cx)) + cy);
	vect.push_back(cz);
	return vect;
}

void Gen_UVsphere(vector <float>& vert, int acc, float cx, float cy, float cz, float r) {
	float th = 360.0f / float(acc);
	for (int i = 0; i < int(ceil(acc / 2)); i++) {
		vector<float> a = Ngonyz(cx, cy, cz, cx, cy + r, cz, th, i);
		float rada = (cz - a[2]);
		vector<float> b = Ngonyz(cx, cy, cz, cx, cy + r, cz, th, i + 1);
		float radb = (cz - b[2]);

		for (int j = 0; j < acc; j++) {
			vector<float> pa = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j);
			vector<float> pb = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j + 1);
			vector<float> pc = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j);
			vector<float> pd = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j + 1);

			Gen_3dquad(vert, pd[0], pd[1], pd[2], pc[0], pc[1], pc[2], pb[0], pb[1], pb[2], pa[0], pa[1], pa[2]);
		}
	}
}

void Gen_Doughnut(vector <float>& vert, int acc, float cx, float cy, float cz, float r, float thi) {
	float th = 360.0f / float(acc);
	thi /= 2.0f;
	for (int i = 0; i < acc; i++) {
		vector<float> a = Ngonyz(cx, cy, cz + r - thi, cx, cy, cz + r, th, i);
		float rada = abs(a[2] - cz);
		vector<float> b = Ngonyz(cx, cy, cz + r - thi, cx, cy, cz + r, th, i + 1);
		float radb = b[2] - cz;
	

		for (int j = 0; j < acc; j++) {
			vector<float> pa = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j);
			vector<float> pb = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j + 1);

			vector<float> pc = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j);
			vector<float> pd = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j + 1);

			//Gen_3dtriangle(vert, cx, cy, cz, pa[0], pa[1], pa[2], pb[0], pb[1], pb[2]);
			Gen_3dquad(vert, pd[0], pd[1], pd[2], pc[0], pc[1], pc[2], pb[0], pb[1], pb[2], pa[0], pa[1], pa[2]);

		}
	}
}

void Gen_Cone(vector<float>& vert, int acc, float cx, float cy, float cz, float r, float h) {
	float th = 360.0f / float(acc);
	for (int i = 0; i < acc; i++) {
		vector<float> pa = Ngonxz(cx, cy, cz, cx, cy, cz + r, th, i);
		vector<float> pb = Ngonxz(cx, cy, cz, cx, cy, cz + r, th, i + 1);

		Gen_3dtriangle(vert, pa[0], pa[1], pa[2], pb[0], pb[1], pb[2], cx, cy + h, cz);
		Gen_3dtriangle(vert, pa[0], pa[1], pa[2], pb[0], pb[1], pb[2], cx, cy, cz);

	}
}

void Gen_Cylinder(vector<float>& vert, int acc, float cx, float cy, float cz, float r, float h) {
	float th = 360.0f / float(acc);
	for (int i = 0; i < acc; i++) {
		vector<float> pa = Ngonxz(cx, cy, cz, cx, cy, cz + r, th, i);
		vector<float> pb = Ngonxz(cx, cy, cz, cx, cy, cz + r, th, i + 1);

		Gen_3dquad(vert, pb[0], pb[1] + h, pb[2], pa[0], pa[1] + h, pa[2], pb[0], pb[1], pb[2],pa[0], pa[1], pa[2]);

		Gen_3dtriangle(vert, pa[0], pa[1], pa[2], pb[0], pb[1], pb[2], cx, cy, cz);
		Gen_3dtriangle(vert, pa[0], pa[1] + h, pa[2], pb[0], pb[1] + h, pb[2], cx, cy + h, cz);
		
	}
}

