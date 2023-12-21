#include "CsvIterator.h"
#include "MovingAverage.h"
#include <iostream>

int main()
{
	//CsvIterator temp("C:/Users/nrnaz/Downloads/YU.L.csv");
    CsvIterator temp("C:/Users/Nazim/Source/Repos/NaRo747/BackTestingLibrary/BackTestingLibrary/YU.L.csv");

    // Call the function to get the iterator to the first pair
    auto firstPairIterator = temp.GetFirst();


    // Access the key and value of the first pair
    std::string key = firstPairIterator->first;
    std::vector<float> values = firstPairIterator->second;


    auto temp_price_data = temp.GetClose("2022-07-19", "2023-12-15");
    
    if (temp_price_data != nullptr)
    {
        for (const auto& entry : *temp_price_data) {
            std::cout << entry.first << "\t" << entry.second << std::endl;
        }
    }

    std::cout << "*******************************************" << std::endl << std::endl;
    /*
    std::map<std::string, float> price_data = {
        {"2023-01-01", 150.5},
        {"2023-01-02", 152.3},
        {"2023-01-03", 148.7},
        {"2023-01-04", 155.2},
        {"2023-01-05", 160.8},
        {"2023-01-06", 158.6},
        {"2023-01-07", 161.2},
        {"2023-01-08", 157.4},
        {"2023-01-09", 159.9},
        {"2023-01-10", 155.7},
        {"2023-01-11", 154.3},
        {"2023-01-12", 157.8},
        {"2023-01-13", 156.1},
        {"2023-01-14", 159.0},
        {"2023-01-15", 152.6},
        {"2023-01-16", 151.8},
        {"2023-01-17", 153.5},
        {"2023-01-18", 150.2},
        {"2023-01-19", 148.9},
        {"2023-01-20", 155.5}
    };*/
    int window_size = 20;

    auto *ref = temp_price_data.get();

    MovingAverage mv_ave(window_size, ref);

    auto average = mv_ave.GetMovingAverage();

    for (const auto& entry : average) {
        std::cout << entry.first << "\t" << entry.second << std::endl;
    }

	return 0;
}