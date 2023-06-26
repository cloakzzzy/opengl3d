#pragma once
#include<CL/opencl.h>
#include<cassert>
#include<vector>

using namespace std;

class Context
{
private:
	cl_int contextResult;
	vector<cl_mem> buffers;
public:
	cl_context id;

	Context(cl_device_id device) {
		id = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &contextResult);
		assert(contextResult == CL_SUCCESS);
	}

	cl_mem CreateBuffer(cl_mem_flags flags, size_t size) {
		cl_int bufferResult;
		cl_mem buffer = clCreateBuffer(id, flags, size, nullptr, &bufferResult);
		assert(bufferResult == CL_SUCCESS);
		buffers.push_back(buffer);
		return buffer;
	}

	~Context() {
		for (cl_mem b : buffers) {
			clReleaseMemObject(b);
		}
		clReleaseContext(id);
	}
};