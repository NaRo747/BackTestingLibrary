#include "CsvIterator.h"
#include "MovingAverage.h"
#include <iostream>

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

int main()
{
	//CsvIterator temp("C:/Users/nrnaz/Downloads/YU.L.csv");
    CsvIterator temp("C:/Users/Nazim/Source/Repos/NaRo747/BackTestingLibrary/BackTestingLibrary/YU.L.csv");

    // Call the function to get the iterator to the first pair
    auto firstPairIterator = temp.GetFirst();


    // Access the key and value of the first pair
    std::string key = firstPairIterator->first;
    std::vector<float> values = firstPairIterator->second;


    auto temp_price_data = temp.GetClose("2022-09-29", "2023-12-18");
    
    /*
    if (temp_price_data != nullptr)
    {
        for (const auto& entry : *temp_price_data) {
            std::cout << entry.first << "\t" << entry.second << std::endl;
        }
    }
    

    std::cout << "*******************************************" << std::endl << std::endl;
    */

    auto *ref = temp_price_data.get();

    MovingAverage mv_ave(20, ref);
    MovingAverage mv_ave2(50, ref);
    /*
    auto average = mv_ave.GetMovingAverage();
    auto average2 = mv_ave2.GetMovingAverage();
    
    for (const auto& entry : average) {
        std::cout << entry.first << "\t" << entry.second << std::endl;
    }

    std::cout << "*******************************************" << std::endl << std::endl;

    for (const auto& entry : average2) {
        std::cout << entry.first << "\t" << entry.second << std::endl;
    }
    
    for (const auto& entry : mv_ave.ListCrosses("2022-10-28", "2023-12-15")) {
        std::cout << entry.first << "\t" << as_integer(entry.second) << std::endl;
    }*/

    std::cout << "Crosses? " << as_integer(mv_ave.HasCrossed(mv_ave2, "2023-05-11")) << std::endl;
    

	return 0;
}