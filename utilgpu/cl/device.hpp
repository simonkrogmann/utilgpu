#pragma once
#include "device.h"

#include <string>

namespace cl
{
template <typename T>
T deviceInfo(cl_device_id device, cl_device_info param)
{
    T info;
    clGetDeviceInfo(device, param, sizeof(info), &info, nullptr);
    return info;
}
}  // namespace cl
