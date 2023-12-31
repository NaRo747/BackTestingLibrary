#pragma once
#include <map>
#include <string>
#include <vector>

enum class BoughtStatus
{
	over_bought, // The stock is over bought as it has passed the upper threshold.
	middle,      // The stock is between thresholds.
	over_sold    // The stock is over sold as it has passed the lower threshold.
};

class RelativeStrengthIndex
{
private:
	int period;
	std::map<std::string, double>* price_data;
	std::map<std::string, double> relative_strength_index;
	int upper_threshold;
	int lower_threshold;
public:
	RelativeStrengthIndex() = default;
	RelativeStrengthIndex(int period, std::map<std::string, double>* price_data, int upper_threshold = 70, int lower_threshold = 30);
	bool SetPeriod(int period);
	int GetPeriod();
	void CalculateRelativeStrengthIndex();
	std::map<std::string, BoughtStatus> ListCrosses();
};

