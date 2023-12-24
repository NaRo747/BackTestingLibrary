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

float MovingAverage::GetGradient()
{
	return this->gradient;
}

int MovingAverage::GetWindowSize()
{
	return this->window_size;
}

/*
* This version of HasCrossed returns true if this object has crossed 
*/
CrossReturn MovingAverage::HasCrossed(MovingAverage &sma, std::string date)
{
	auto this_date_itr = this->moving_average.find(date);
	auto temp = sma.GetMovingAverage();
	auto sma_date_itr = temp.find(date);
	float this_orig_value = this_date_itr->second;
	float sma_orig_value = sma_date_itr->second;

	// Validate that there is a previous value to check cross direction. If there is not, there is no cross.
	if (this_date_itr != this->moving_average.begin() && sma_date_itr != temp.begin())
	{
		this_date_itr--;
		sma_date_itr--;

		return this->CrossGradient(this_orig_value, sma_orig_value, this_date_itr->second, sma_date_itr->second);
	}

	return CrossReturn::no_cross;
}

std::map<std::string, CrossReturn> MovingAverage::ListCrosses(std::string start_date, std::string end_date)
{
	std::map<std::string, CrossReturn> cross_events;
	auto moving_average_itr = this->moving_average.find(start_date);
	auto price_itr = this->price_data->find(start_date);
	float moving_average_value{ 0 };
	float price_value{ 0 };
	CrossReturn cross_status{};

	if (moving_average_itr == this->moving_average.end() || price_itr == this->price_data->end())
	{
		std::cerr << "Invalid start date (" << start_date << ") entered." << std::endl;
	}
	else
	{
		while (moving_average_itr->first != end_date)
		{
			moving_average_value = moving_average_itr->second;
			price_value = price_itr->second;
			moving_average_itr++;
			price_itr++;

			// This order means the return is referring to the share price crossing the moving average.
			cross_status = this->CrossGradient(price_itr->second, moving_average_itr->second, price_value, moving_average_value);
			if (cross_status != CrossReturn::no_cross)
			{
				cross_events.insert({ moving_average_itr->first, cross_status });
			}
		}
	}

	return cross_events;
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

	this->gradient = this->CalculateGradient();
	

}

float MovingAverage::CalculateGradient()
{
	// Using window_size datapoints from the most recent data of the plot will indicate to use the movement of the price.

	auto datapoint_one_itr = this->moving_average.rbegin();
	auto datapoint_two_itr = std::next(datapoint_one_itr, this->window_size);

	return (datapoint_one_itr->second - datapoint_two_itr->second) / this->window_size;
}

CrossReturn MovingAverage::CrossGradient(float orig_value1, float orig_value2, float prev_value1, float prev_value2)
{
	// If dates value is either larger or equal, it means that there is potential for 
	if (orig_value1 >= orig_value2)
	{
		return (prev_value1 < prev_value2) ? CrossReturn::positive_cross : CrossReturn::no_cross;
	}
	else
	{
		return (prev_value1 > prev_value2) ? CrossReturn::negative_cross : CrossReturn::no_cross;
	}

}
