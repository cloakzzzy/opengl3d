#pragma once
#include<CL/opencl.h>
#include<cassert>

using namespace std;

class Queue
{
private:
	cl_int commandQueueResult;
public:
	cl_command_queue id;
	Queue(cl_device_id device, cl_context context) {
		id = clCreateCommandQueue(context, device, 0, &commandQueueResult);
		assert(commandQueueResult == CL_SUCCESS);
	}

	void EnqueueWriteBuffer(cl_mem buffer, const void* ptr, size_t size, size_t offset) {
		cl_int enqueueBufferResult = clEnqueueWriteBuffer(id, buffer, CL_TRUE, offset, size, ptr, 0, nullptr, nullptr);
		assert(enqueueBufferResult == CL_SUCCESS);
	}

	void EnqueueReadBuffer(cl_mem buffer, void* ptr, size_t size, size_t offset) {
		cl_int enqueueBufferResult = clEnqueueReadBuffer(id, buffer, CL_TRUE, offset, size, ptr, 0, nullptr, nullptr);
		assert(enqueueBufferResult == CL_SUCCESS);
	}

	void EnqueueNDRangeKernel(cl_kernel kernel, cl_uint workdim, const size_t *global_work_offset, const size_t *globalworksize, const size_t *localworksize) {
		cl_int enqueueKernelResult = clEnqueueNDRangeKernel(id, kernel,workdim, global_work_offset, globalworksize, localworksize, 0, nullptr, nullptr);
		assert(enqueueKernelResult == CL_SUCCESS);
	}

	void Finish() {
		clFinish(id);
	}

	~Queue() {
		clReleaseCommandQueue(id);
	}
};