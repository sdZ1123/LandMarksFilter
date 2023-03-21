
#ifndef MEDIAPIPE_UTIL_FILTERING_RELATIVE_VELOCITY_FILTER_H_
#define MEDIAPIPE_UTIL_FILTERING_RELATIVE_VELOCITY_FILTER_H_

#include <deque>
#include <memory>
#include "landmarks_smoothApi.h"
#include "absl/time/time.h"
#include "low_pass_filter.h"


namespace mediapipe {

	// This filter keeps track (on a window of specified size) of
	// value changes over time, which as result gives us velocity of how value
	// changes over time. With higher velocity it weights new values higher.
	//
	// Use @window_size and @velocity_scale to tweak this filter for your use case.
	//
	// - higher @window_size adds to lag and to stability
	// - lower @velocity_scale adds to lag and to stability
	class RelativeVelocityFilter
	{
	public:
		

	public:
		RelativeVelocityFilter(size_t window_size, float velocity_scale,
			DistanceEstimationMode distance_mode) : max_window_size_(window_size),
			window_(window_size),
			velocity_scale_(velocity_scale),
			distance_mode_(distance_mode)
		{

		}

		RelativeVelocityFilter(size_t window_size, float velocity_scale)
			: RelativeVelocityFilter{ window_size, velocity_scale,
									 DistanceEstimationMode::kDefault } {}

		// Applies filter to the value.
		// @timestamp - timestamp associated with the value (for instance,
		//              timestamp of the frame where you got value from)
		// @value_scale - value scale (for instance, if your value is a distance
		//                detected on a frame, it can look same on different
		//                devices but have quite different absolute values due
		//                to different resolution, you should come up with an
		//                appropriate parameter for your particular use case)
		// @value - value to filter


		float Apply(const double timestamp, float value_scale, float value);

	private:
		struct WindowElement {
			float distance;
			int64_t duration;
		};

		float last_value_{ 0.0 };
		float last_value_scale_{ 1.0 };
		int64_t last_timestamp_{ -1 };

		size_t max_window_size_;
		std::deque<WindowElement> window_;
		LowPassFilter low_pass_filter_{ 1.0f };
		float velocity_scale_;
		DistanceEstimationMode distance_mode_;
	};

}  // namespace mediapipe

#endif  // MEDIAPIPE_UTIL_FILTERING_RELATIVE_VELOCITY_FILTER_H_
