#pragma once
#include <map>
#include <string>

enum class CrossReturn
{
	positive_cross,  // The object's SMA has crossed the other's due to higher gradient.
	no_cross,        // The object's SMA has not crossed the others.
	negative_cross   // The object's SMA has crossed the other's due to lower gradient.
};


class MovingAverage
{
public:
	MovingAverage() = default;
	MovingAverage(int window_size, std::map<std::string, float>* price_data);
	~MovingAverage() = default;
	void UpdateWindowSize(int window_size);
	void AddData(std::map<std::string, float> price_data);
	std::map<std::string, float> GetMovingAverage();
	float GetGradient();
	int GetWindowSize();
	CrossReturn HasCrossed(MovingAverage &sma, std::string date);
	std::map<std::string, CrossReturn> ListCrosses(std::string start_date, std::string end_date);
private:
	std::map<std::string, float>* price_data;
	std::map<std::string, float> moving_average;
	float gradient;
	int window_size;
	void CalculateMovingAverage();
	float CalculateGradient();
	CrossReturn CrossGradient(float orig_value1, float orig_value2, float prev_value1, float prev_value2);
};

