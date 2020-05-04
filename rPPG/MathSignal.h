#pragma once
#include <cmath>
#include <vector>
#include <numeric>
#include <string>
#include <functional>


class MathSignal {
public:
	static float DetrendData( float red_value) {

		std::vector<float> data_buffer;
		
		
		float avg = std::accumulate(data_buffer.begin(), data_buffer.end(),0.0) / data_buffer.size();

		//Remove any high values in signal
		if (std::abs(red_value - avg) > 10 && data_buffer.size() > 99)
			red_value = *(data_buffer.end());

		

		data_buffer.emplace_back(red_value);
		return red_value;
	}

};