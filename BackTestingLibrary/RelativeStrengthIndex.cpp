#include "RelativeStrengthIndex.h"
#include <iostream>
#include <vector>

RelativeStrengthIndex::RelativeStrengthIndex(int period, std::map<std::string, double>* price_data, int upper_threshold, int lower_threshold) : period{period}, price_data{price_data}, upper_threshold{upper_threshold}, lower_threshold{lower_threshold}
{
	this->CalculateRelativeStrengthIndex();
}

bool RelativeStrengthIndex::SetPeriod(int period)
{
	this->period = period;
	this->CalculateRelativeStrengthIndex();
	return true;
}

int RelativeStrengthIndex::GetPeriod()
{
	return this->period;
}

void RelativeStrengthIndex::CalculateRelativeStrengthIndex()
{
    int dataSize = static_cast<int>(this->price_data->size());
    auto price_data_itr = this->price_data->begin();
    std::vector<double> gains;
    std::vector<double> losses;

    if (dataSize < this->period + 1) 
    {
        std::cerr << "Insufficient data for RSI calculation." << std::endl;
        return; // Error value
    }

    
    // Calculate gains and losses
    for (int i = 1; i < dataSize; ++i) 
    {
        double priceDiff = (-price_data_itr->second) + (++price_data_itr)->second;

        if (priceDiff > 0) 
        {
            gains.push_back(priceDiff);
            losses.push_back(0);
        }
        else if (priceDiff < 0) {
            gains.push_back(0);
            losses.push_back(-priceDiff);
        }
        else {
            gains.push_back(0);
            losses.push_back(0);
        }
    }

    auto rsi_data_itr = std::next(this->price_data->begin(), this->period );

    // Calculate average gains and losses over the specified period
    double avgGain{ 0 };
    double avgLoss{ 0 };

    for (int i = 0; i < this->period; ++i) {
        avgGain += gains[i];
        avgLoss += losses[i];
    }

    avgGain /= this->period;
    avgLoss /= this->period;

    // Calculate RSI
    for (int i = this->period -1; i < dataSize - 1; ++i) {

        avgGain = ((this->period - 1) * avgGain + gains[i]) / this->period;
        avgLoss = ((this->period - 1) * avgLoss + losses[i]) / this->period;

        double relativeStrength = avgGain / (avgLoss == 0 ? 1e-6 : avgLoss); // Prevent division by zero
        this->relative_strength_index.insert({ rsi_data_itr->first, 100 - (100 / (1 + relativeStrength))});
        std::cout << rsi_data_itr->first << " : " << 100 - (100 / (1 + relativeStrength)) << std::endl;
        rsi_data_itr++;
    }
}



std::map<std::string, BoughtStatus> RelativeStrengthIndex::ListCrosses()
{
    std::map<std::string, BoughtStatus> rsi_crosses;

    for (const auto& data_point : this->relative_strength_index)
    {
        if (data_point.second >= static_cast<double>(this->upper_threshold))
        {
            rsi_crosses.insert({ data_point.first, BoughtStatus::over_bought });
        }
        else if (data_point.second <= static_cast<double>(this->lower_threshold))
        {
            rsi_crosses.insert({ data_point.first, BoughtStatus::over_sold });
        }
    }

    return rsi_crosses;
}
