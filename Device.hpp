#pragma once
#include<CL/opencl.h>
#include<cassert>
#include<string>

using namespace std;

class Device
{
private:

public:
	cl_device_id id;

	Device(const char* vendorname) {
        cl_platform_id platforms[64];
        unsigned int platformCount;
        cl_int platformResult = clGetPlatformIDs(64, platforms, &platformCount);
        assert(platformResult == CL_SUCCESS);

        id = nullptr;
        for (int i = 0; i < platformCount && id == nullptr; ++i) {
            cl_device_id devices[64];
            unsigned int deviceCount;
            cl_int deviceResult = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 64, devices, &deviceCount);
            if (deviceResult == CL_SUCCESS) {
                for (int j = 0; j < deviceCount; ++j) {
                    char vendorName[256];
                    size_t vendorNameLength;
                    cl_int deviceInfoResult = clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 256, vendorName, &vendorNameLength);
                    if (deviceInfoResult == CL_SUCCESS && std::string(vendorName).substr(0, vendorNameLength) == vendorname) {
                        id = devices[j];
                        break;
                    }
                }
            }
        }
	}

    ~Device() {
        clReleaseDevice(id);
    }

};