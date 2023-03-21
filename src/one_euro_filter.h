#ifndef MEDIAPIPE_UTIL_FILTERING_ONE_EURO_FILTER_H_
#define MEDIAPIPE_UTIL_FILTERING_ONE_EURO_FILTER_H_

#include <memory>

#include "absl/time/time.h"
#include "low_pass_filter.h"
#include "landmarks_smoothApi.h"

#define M_PI 3.141592617

namespace mediapipe {

	class OneEuroFilter
	{
	public:
		OneEuroFilter(double frequency, double min_cutoff, double beta,
			double derivate_cutoff);

		double Apply(const double timestamp, double value_scale, double value);

	private:
		double GetAlpha(double cutoff);

		void SetFrequency(double frequency);

		void SetMinCutoff(double min_cutoff);

		void SetBeta(double beta);

		void SetDerivateCutoff(double derivate_cutoff);

		double frequency_;
		double min_cutoff_;
		double beta_;
		double derivate_cutoff_;
		std::unique_ptr<LowPassFilter> x_;
		std::unique_ptr<LowPassFilter> dx_;
		int64_t last_time_;
	};

}  // namespace mediapipe

#endif  // MEDIAPIPE_UTIL_FILTERING_ONE_EURO_FILTER_H_
