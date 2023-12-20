#include "CsvIterator.h"
#include <iostream>

int main()
{
	CsvIterator temp("C:/Users/nrnaz/Downloads/YU.L.csv");

    // Call the function to get the iterator to the first pair
    auto firstPairIterator = temp.GetFirst();


    // Access the key and value of the first pair
    std::string key = firstPairIterator->first;
    std::vector<float> values = firstPairIterator->second;


    auto temp_itr = temp.GetOpen("2022-07-21", "2022-08-01");

    if (temp_itr != nullptr)
    {
        for (const auto& element : *temp_itr) {
            std::cout << element << std::endl;
        }
    }

	return 0;
}