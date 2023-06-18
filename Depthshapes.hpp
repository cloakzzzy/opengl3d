#pragma once
#include <math.h>
#include "libs/glm/glm.hpp"
#include <vector>
#include"Flatshapes.hpp"



void Gen_UVsphere(vector <float>& vert, int acc, float cx, float cy, float cz, float r) {
	int layers = int(ceil(acc / 2));
	float th = 360.0f / float(acc);
	for (int i = 0; i < layers; i++) {
		vector<float> a = Ngonyz(cx, cy, cz, cx, cy + r, cz, th, i);
		float rada = abs(cz - a[2]);
		vector<float> b = Ngonyz(cx, cy, cz, cx, cy + r, cz, th, i + 1);
		float radb = abs(cz - b[2]);

		for (int j = 0; j < acc; j++) {
			vector<float> pa = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j);
			vector<float> pb = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j + 1);
			vector<float> pc = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j);
			vector<float> pd = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j + 1);

			Gen_3dquad(vert, pd[0], pd[1], pd[2], pc[0], pc[1], pc[2], pb[0], pb[1], pb[2], pa[0], pa[1], pa[2]);
		}
	}
}

void Gen_Doughnut(vector <float>& vert, int acc, float cx, float cy, float cz, float r, float thickness) {
	float th = 360.0f / float(acc);

	for (int i = 0; i < acc; i++) {
		vector<float> a = Ngonyz(cx, cy, cz + r - thickness / 2.0f, cx, cy, cz + r, th, i);
		float rada = abs(a[2] - cz);
		vector<float> b = Ngonyz(cx, cy, cz + r - thickness / 2.0f, cx, cy, cz + r, th, i + 1);
		float radb = abs(b[2] - cz);
		
		for (int j = 0; j < acc; j++) {
			vector<float> pa = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j);
			vector<float> pb = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j + 1);
			vector<float> pc = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j);
			vector<float> pd = Ngonxz(cx, b[1], cz, cx, b[1], cz + radb, th, j + 1);

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

//circle
void Gen_Ngonxy(vector <float>& vert, int acc, float cx, float cy, float cz, float r) {
	float th = 360.0f / float(acc);
	for (int i = 0; i < acc; i++) {
		vector<float> pa = Ngonxy(cx, cy, cz, cx + r, cy, cz, th, i);
		vector<float> pb = Ngonxy(cx, cy, cz, cx + r, cy, cz, th, i + 1);
		
		Gen_3dtriangle(vert, pa[0], pa[1], pa[2], pb[0], pb[1], pb[2], cx, cy, cz);
	}
}

//oval
void Gen_Ngonxy(vector <float>& vert, int acc, float cx, float cy, float cz, float ra, float rb) {
	float th = 360.0f / float(acc);
	for (int i = 0; i < acc; i++) {
		vector<float> pa = Ngonxy(cx, cy, cz, cx, cy + ra, cz, cx, cy + rb, cz,th, i);
		vector<float> pb = Ngonxy(cx, cy, cz, cx, cy + ra, cz, cx, cy + rb, cz,th, i + 1);
		Gen_3dtriangle(vert, pa[0], pa[1], pa[2], pb[0], pb[1], pb[2], cx, cy, cz);
	}
}

