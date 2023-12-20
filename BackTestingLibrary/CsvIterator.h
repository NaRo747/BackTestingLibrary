#pragma once
#include <memory>
#include <string>
#include <vector>
#include <map>


class CsvIterator
{
public:
	CsvIterator(std::string data_file_path);
	~CsvIterator() = default;
	std::map<std::string, std::vector<float>> GetPriceVector(std::string date);
	std::vector<float> next();
	std::vector<float> previous();
	std::map<std::string, std::vector<float>>::iterator GetFirst();
	std::map<std::string, std::vector<float>>::iterator GetLast();
	std::unique_ptr<std::vector<float>> GetOpen(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<float>> GetHigh(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<float>> GetLow(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<float>> GetClose(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<float>> GetAdjustClose(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<float>> GetVolume(std::string start_date, std::string end_date);

private:
	std::string ticker;

	/* The CSV will be in the following order:
	*  Date : Open,High,Low,Close,Adj Close,Volume
	*/ 
	std::map<std::string, std::vector<float>> price_data;
	std::map<std::string, std::vector<float>>::iterator data_itr;
	std::unique_ptr<std::vector<float>> GetPriceData(std::string start_date, std::string end_date, int position);


};

