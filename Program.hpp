#pragma once
#include<CL/opencl.h>
#include<cassert>
#include <string>
#include<fstream>

using namespace std;

static std::string read_file(const char* fileName) {
    std::fstream f;
    f.open(fileName, std::ios_base::in);
    assert(f.is_open());
    std::string res;
    while (!f.eof()) {
        char c;
        f.get(c);
        res += c;
    }
    f.close();
    return std::move(res);
}

class Program
{
private:
    cl_int programResult;
    size_t length = 0;
public:
    cl_program id;
	Program(const char* filename, cl_device_id device, cl_context context) {
        std::string s = read_file(filename);
        const char* programSource = s.c_str();

        id = clCreateProgramWithSource(context, 1, &programSource, &length, &programResult);
        assert(programResult == CL_SUCCESS);

        cl_int programBuildResult = clBuildProgram(id, 1, &device, "", nullptr, nullptr);
        if (programBuildResult != CL_SUCCESS) {
            char log[256];
            size_t logLength;
            cl_int programBuildInfoResult = clGetProgramBuildInfo(id, device, CL_PROGRAM_BUILD_LOG, 256, log, &logLength);
            cout << log << '\n';
        }
	}
    ~Program() {
        clReleaseProgram(id);
    }

};