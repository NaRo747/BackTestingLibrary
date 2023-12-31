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
	std::map<std::string, std::vector<double>> GetPriceVector(std::string date);
	std::vector<double> next();
	std::vector<double> previous();
	std::map<std::string, std::vector<double>>::iterator GetFirst();
	std::map<std::string, std::vector<double>>::iterator GetLast();
	void addEntry(std::string date, std::vector<double> price_data);
	std::unique_ptr<std::vector<double>> GetOpenValue(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<double>> GetHighValue(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<double>> GetLowValue(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<double>> GetCloseValue(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<double>> GetAdjustCloseValue(std::string start_date, std::string end_date);
	std::unique_ptr<std::vector<double>> GetVolumeValue(std::string start_date, std::string end_date);

	std::unique_ptr<std::map<std::string, double>>GetOpen(std::string start_date, std::string end_date);
	std::unique_ptr<std::map<std::string, double>>GetHigh(std::string start_date, std::string end_date);
	std::unique_ptr<std::map<std::string, double>>GetLow(std::string start_date, std::string end_date);
	std::unique_ptr<std::map<std::string, double>>GetClose(std::string start_date, std::string end_date);
	std::unique_ptr<std::map<std::string, double>>GetAdjustClose(std::string start_date, std::string end_date);
	std::unique_ptr<std::map<std::string, double>>GetVolume(std::string start_date, std::string end_date);

private:
	std::string ticker;
	std::string file_path;

	/* The CSV will be in the following order:
	*  Date : Open,High,Low,Close,Adj Close,Volume
	*/ 
	std::map<std::string, std::vector<double>> price_data;
	std::map<std::string, std::vector<double>>::iterator data_itr;
	std::unique_ptr<std::vector<double>> GetPriceDataValue(std::string start_date, std::string end_date, int position);
	std::unique_ptr<std::map<std::string, double>>GetPriceData(std::string start_date, std::string end_date, int position);


};

