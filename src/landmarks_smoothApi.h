#pragma once
#include <opencv.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#ifdef EXPORT_DLL
#define EXPORT_DLL extern "C" __declspec(dllexport)
#else
#define EXPORT_DLL extern "C" __declspec(dllimport)
#endif


enum DistanceEstimationMode {
	// When the value scale changes, uses a heuristic
	// that is not translation invariant (see the implementation for details).
	kLegacyTransition,
	// The current (i.e. last) value scale is always used for scale estimation.
	// When using this mode, the filter is translation invariant, i.e.
	//     Filter(Data + Offset) = Filter(Data) + Offset.
	kForceCurrentScale,

	kDefault = kLegacyTransition
};

struct MConfig
{
	//VelocityFilter  or OneEuroFilter
	//input : VelocityFilter or OneEuroFilter
	std::string pattern;
	int points2dSize;

	//VelocityFilter input param
	size_t window_size;
	float velocity_scale;
	DistanceEstimationMode distance_mode;
	//OneEuroFilter input param
	double frequency=120; //120 Hz 
	double min_cutoff=1.0;  //��С��ֹƵ��(������С��ֹƵ�ʻή�����ٶ��������������ӳ�)
	double beta=0.007; //�ٶ�ϵ���������ٶ�ϵ��������ٶ��ͺ����Ӷ�����
	double derivate_cutoff=1.0;
};

struct MediaPipeData
{
	std::vector<cv::Point3f> pose;
	std::vector<cv::Point2f> leftHandPose;
	std::vector<cv::Point2f> rightHandPose;
	std::vector<cv::Point3f> facePose;
};


class LandMarkSmoothApi
{
public:
	virtual bool Filter(
		const MediaPipeData& in_lanmark,
		const float value_scale,
		const double timesstamp,
		MediaPipeData &out_landmark) = 0;

};

EXPORT_DLL LandMarkSmoothApi* CreateObject(const MConfig & _config);
EXPORT_DLL bool Release(LandMarkSmoothApi* ptr);


