#pragma once
#include "landmarks_smoothApi.h"
#include "relative_velocity_filter.h"
#include "one_euro_filter.h"

class LandMarkSmooth:public LandMarkSmoothApi
{
public:
	LandMarkSmooth(const MConfig&_config);
	bool Filter(
		const MediaPipeData& in_lanmark,
		const float value_scale,
		const double timesstamp,
		MediaPipeData& out_landmark)override;

private:
	std::vector<std::unique_ptr<mediapipe::RelativeVelocityFilter>> p_velyfs;
	std::vector<std::unique_ptr<mediapipe::OneEuroFilter>> p_oneEfs;

	/*std::vector<mediapipe::RelativeVelocityFilter *> p_velyfs;
	std::vector<mediapipe::OneEuroFilter*> p_oneEfs;*/
	MConfig config;
};

