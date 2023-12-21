#include "MovingAverage.h"
#include <iostream>
#include <deque>
#include <string>

MovingAverage::MovingAverage(int window_size, std::map<std::string, float> *price_data)
{
	this->window_size = window_size;
	this->price_data = price_data;

	this->CalculateMovingAverage();
}

void MovingAverage::UpdateWindowSize(int window_size)
{
	this->window_size = window_size;
	this->CalculateMovingAverage();
}

void MovingAverage::AddData(std::map<std::string, float> price_data)
{
	this->price_data->insert(price_data.begin(), price_data.end());
	this->CalculateMovingAverage();
}

std::map<std::string, float> MovingAverage::GetMovingAverage()
{
	return this->moving_average;
}

int MovingAverage::GetWindowSize()
{
	return this->window_size;
}

void MovingAverage::CalculateMovingAverage()
{
	/* The price data will be closing prices for the stock.
	*  The data will be labelled with the date. The moving average is calculated using the window_size.
	*  The first data point in moving_average will be window_size datapoints into the data.
	*  The average of the first window_size points should be calculated then stored, this represents the first datapoint.
	*  From then the last data point will be removed and the new one added and the average value is recalculated.
	*/

	auto data_itr = this->price_data->begin();
	std::map<std::string, float>::iterator data_itr_end = this->price_data->end();
	std::deque<float> window_deque;
	float window_average{ 0 };
	float sum{ 0 };

	
	if (this->window_size > this->price_data->size())
	{
		std::cerr << this->price_data->size() << " Elements in price_data, window_size(" << this->window_size << ") too large. Not enough data." << std::endl;
		return;
	}
	else
	{
		data_itr_end = std::next(data_itr, this->window_size - 1);
	}
	

	// Calculate sum of first window_size elements
	for (; data_itr != data_itr_end; data_itr++)
	{
		window_deque.push_back(data_itr->second);
		sum += data_itr->second;
	}

	// Calculate Moving Average.
	for (; data_itr != this->price_data->end(); ++data_itr)
	{
		sum += data_itr->second;
		window_deque.push_back(data_itr->second);
		window_average = sum / this->window_size;
		this->moving_average.insert({ data_itr->first, window_average });
		sum -= window_deque.front();
		window_deque.pop_front();
	}
	

}
