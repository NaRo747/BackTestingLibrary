#include "CsvIterator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <map>


CsvIterator::CsvIterator(std::string data_file_path)
{
    // Open file as a stream.
    std::ifstream data_file(data_file_path, std::ifstream::in);
    std::string line;

    // Find the last occurrence of '/' and the dot '.'
    size_t lastSlash = data_file_path.find_last_of('/');
    size_t lastDot = data_file_path.find_last_of('.');


    // Attempt to set ticker name in object.
    if (lastSlash != std::string::npos && lastDot != std::string::npos && lastDot > lastSlash) {
        // Extract the substring between the last '/' and the last '.'
        std::string ticker_name = data_file_path.substr(lastSlash + 1, lastDot - lastSlash - 1);

        std::cout << "Working on ticker: " << ticker_name << std::endl;
        this->ticker = ticker_name;
    }
    else {
        std::cerr << "Invalid file path format." << std::endl;
    }

    if (!data_file.is_open())
    {
        std::cerr << "Error opening file" << data_file_path << std::endl;
    }
    else
    {
        // Ignore headers at the top of csv.
        std::getline(data_file, line);

        while (std::getline(data_file, line))
        {
            std::istringstream ss(line);
            std::string datapoint{};
            std::vector<float> price_info{};
            std::string date{};

            std::getline(ss, datapoint, ',');
            date = datapoint;

            while (std::getline(ss, datapoint, ','))
            {
                // Convert datapoint to a float and add to end of vector.
                price_info.push_back(stof(datapoint));
            }

            this->price_data.insert({ date, price_info });
        }

        // Initialise the iterator.
        this->data_itr = this->price_data.begin();

    }
}

std::map<std::string, std::vector<float>> CsvIterator::GetPriceVector(std::string date)
{
    return std::map<std::string, std::vector<float>>();
}

std::vector<float> CsvIterator::next()
{
    return (this->data_itr++)->second;
}

std::vector<float> CsvIterator::previous()
{
    return (this->data_itr--)->second;
}

std::map<std::string, std::vector<float>>::iterator CsvIterator::GetFirst()
{
    return this->price_data.begin();
}

std::map<std::string, std::vector<float>>::iterator CsvIterator::GetLast()
{
    return this->price_data.end();
}

std::unique_ptr<std::vector<float>> CsvIterator::GetOpenValue(std::string start_date, std::string end_date)
{
    return this->GetPriceDataValue(start_date, end_date, 0);
}

std::unique_ptr<std::vector<float>> CsvIterator::GetHighValue(std::string start_date, std::string end_date)
{
    return this->GetPriceDataValue(start_date, end_date, 1);
}

std::unique_ptr<std::vector<float>> CsvIterator::GetLowValue(std::string start_date, std::string end_date)
{
    return this->GetPriceDataValue(start_date, end_date, 2);
}

std::unique_ptr<std::vector<float>> CsvIterator::GetCloseValue(std::string start_date, std::string end_date)
{
    return this->GetPriceDataValue(start_date, end_date, 3);
}

std::unique_ptr<std::vector<float>> CsvIterator::GetAdjustCloseValue(std::string start_date, std::string end_date)
{
    return this->GetPriceDataValue(start_date, end_date, 4);
}

std::unique_ptr<std::vector<float>> CsvIterator::GetVolumeValue(std::string start_date, std::string end_date)
{
    return this->GetPriceDataValue(start_date, end_date, 5);
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetOpen(std::string start_date, std::string end_date)
{
    return this->GetPriceData(start_date, end_date, 0);
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetHigh(std::string start_date, std::string end_date)
{
    return this->GetPriceData(start_date, end_date, 1);
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetLow(std::string start_date, std::string end_date)
{
    return this->GetPriceData(start_date, end_date, 2);
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetClose(std::string start_date, std::string end_date)
{
    return this->GetPriceData(start_date, end_date, 3);
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetAdjustClose(std::string start_date, std::string end_date)
{
    return this->GetPriceData(start_date, end_date, 4);
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetVolume(std::string start_date, std::string end_date)
{
    return this->GetPriceData(start_date, end_date, 5);
}

std::unique_ptr<std::vector<float>> CsvIterator::GetPriceDataValue(std::string start_date, std::string end_date, int position)
{
    auto start_itr = this->price_data.find(start_date);
    auto end_itr = this->price_data.find(end_date);
    std::unique_ptr<std::vector<float>> sliced_price_data = std::make_unique<std::vector<float>>();

    // Validate dates.
    if (start_itr == this->price_data.end())
    {
        std::cerr << start_date << " is an invalid date" << std::endl;
        return nullptr;
    }

    if (end_itr == this->price_data.end())
    {
        std::cerr << end_date << " is an invalid date" << std::endl;
        return nullptr;
    }

    if (start_itr->first < end_itr->first)
    {
        for (; start_itr->first <= end_itr->first; start_itr++)
            sliced_price_data->push_back(start_itr->second[position]);
    }
    else
    {
        std::cerr << "end_date: " << end_date << " is before the start_date: " << start_date << std::endl;
        return nullptr;
    }


    return sliced_price_data;
}

std::unique_ptr<std::map<std::string, float>> CsvIterator::GetPriceData(std::string start_date, std::string end_date, int position)
{
    auto start_itr = this->price_data.find(start_date);
    auto end_itr = this->price_data.find(end_date);
    std::unique_ptr<std::map<std::string, float>> sliced_price_data = std::make_unique<std::map<std::string, float>>();

    // Validate dates.
    if (start_itr == this->price_data.end())
    {
        std::cerr << start_date << " is an invalid date" << std::endl;
        return nullptr;
    }

    if (end_itr == this->price_data.end())
    {
        std::cerr << end_date << " is an invalid date" << std::endl;
        return nullptr;
    }

    if (start_itr->first < end_itr->first)
    {
        for (; start_itr->first < end_itr->first; start_itr++)
        {
            sliced_price_data->insert({start_itr->first, start_itr->second[position]});
        }

        // Include final element. This is necessary in the event that end_itr is the final element in the map.
        sliced_price_data->insert({ start_itr->first, start_itr->second[position] });
    }
    else
    {
        std::cerr << "end_date: " << end_date << " is before the start_date: " << start_date << std::endl;
        return nullptr;
    }


    return sliced_price_data;
}

