#pragma once
#include <map>
#include <string>


class MovingAverage
{
public:
	MovingAverage() = default;
	MovingAverage(int window_size, std::map<std::string, float> price_data);
	~MovingAverage();
	void UpdateWindowSize(int window_size);
	void AddData(std::map<std::string, float> price_data);
	std::map<std::string, float> GetMovingAverage();
	int GetWindowSize();
private:
	std::map<std::string, float> moving_average;
	int window_size;
	void CalculateMovingAverage();
};

