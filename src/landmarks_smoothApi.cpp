#include "landmarks_smoothApi.h"
#include "landmarks_smooth.h"

LandMarkSmoothApi* CreateObject(const MConfig& _config)
{
	LandMarkSmoothApi* p = new LandMarkSmooth(_config);
	return p;
}

bool Release(LandMarkSmoothApi* ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
		return true;
	}
	else
	{
		return false;
	}
	
}