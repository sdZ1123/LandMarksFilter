#include"landmarks_smooth.h"



LandMarkSmooth::LandMarkSmooth(const MConfig& _config):config(_config)
{
	if(_config.pattern== "VelocityFilter")
	{
		std::cout << "===VelocityFilterInit===" << std::endl;
		int size = _config.points2dSize * 2;
		p_velyfs.resize(size);
		for (int i = 0; i < size; i++)
			/*p_velyfs[i] =new  mediapipe::RelativeVelocityFilter(_config.window_size,
				_config.velocity_scale,
				_config.distance_mode);*/
			p_velyfs[i] = std::make_unique< mediapipe::RelativeVelocityFilter>(
				_config.window_size,
				_config.velocity_scale,
				_config.distance_mode);
	}
	else if(_config.pattern == "OneEuroFilter")
	{
		std::cout << "===OneEuroFilterInit===" << std::endl;
		int size = _config.points2dSize * 2;
		p_oneEfs.resize(size);
		for (int i = 0; i < size; i++)
			/*p_oneEfs[i] = new  mediapipe::OneEuroFilter(_config.frequency,
				_config.min_cutoff,
				_config.beta,
				_config.derivate_cutoff);*/
			p_oneEfs[i] = std::make_unique< mediapipe::OneEuroFilter>(
				_config.frequency,
				_config.min_cutoff,
				_config.beta,
				_config.derivate_cutoff);
		
	}
}

bool LandMarkSmooth::Filter(const MediaPipeData& in_lanmark, const float value_scale, const double timesstamp, MediaPipeData& out_landmark)
{
	
	auto _filter = [&](auto &_pattern) {
		MediaPipeData t_landmark;
		int idx = 0;
		int jdx = 0;
		t_landmark.facePose.resize(in_lanmark.facePose.size());
		for (idx = 0; idx < in_lanmark.facePose.size(); idx++)
		{
			t_landmark.facePose[idx].x =(float) _pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.facePose[idx].x);
			t_landmark.facePose[idx].y = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.facePose[idx].y);
		}
		t_landmark.pose.resize(in_lanmark.pose.size());
		for (idx = 0; idx < in_lanmark.pose.size(); idx++)
		{
			t_landmark.pose[idx].x = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.pose[idx].x);
			t_landmark.pose[idx].y = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.pose[idx].y);
		}
		t_landmark.leftHandPose.resize(in_lanmark.leftHandPose.size());
		for (idx = 0; idx < in_lanmark.leftHandPose.size(); idx++)
		{
			t_landmark.leftHandPose[idx].x = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.leftHandPose[idx].x);
			t_landmark.leftHandPose[idx].y = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.leftHandPose[idx].y);
		}
		t_landmark.rightHandPose.resize(in_lanmark.rightHandPose.size());
		for (idx = 0; idx < in_lanmark.rightHandPose.size(); idx++)
		{
			t_landmark.rightHandPose[idx].x = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.rightHandPose[idx].x);
			t_landmark.rightHandPose[idx].y = (float)_pattern[jdx++]->Apply(timesstamp, value_scale, in_lanmark.rightHandPose[idx].y);
		}
		std::cout << "===FilterRun===" << std::endl;
		return t_landmark;
	};

	if (config.pattern == "VelocityFilter" && p_velyfs.size() > 0)
	{
		out_landmark=_filter(p_velyfs);
		//std::cout << "===VelocityFilterRun===" << std::endl;
		return true;
	}
	else if (config.pattern == "OneEuroFilter" && p_oneEfs.size() > 0)
	{
		out_landmark=_filter(p_oneEfs);
		//std::cout << "===OneEuroFilterRun===" << std::endl;
		return true;
	}
	else
		return false;
}
