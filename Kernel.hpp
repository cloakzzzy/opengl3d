#pragma once
#include<CL/opencl.h>
#include<cassert>
#include<vector>
#include<iostream>

using namespace std;

class Kernel
{
private:
	cl_int kernelResult;
public:
	cl_kernel id;
	Kernel(cl_program program, const char* kernelname) {
		id = clCreateKernel(program, kernelname, &kernelResult);
		cout << kernelResult << '\n';
		assert(kernelResult == CL_SUCCESS);
		
	}

	~Kernel() {
		clReleaseKernel(id);
	}

	void SetArgs(vector<const void*> args) {
		for (int i = 0; i < args.size(); i++) {
			cl_int kernelArgaResult = clSetKernelArg(id, i, sizeof(cl_mem), args[i]);
			assert(kernelArgaResult == CL_SUCCESS);
		}
	}
};