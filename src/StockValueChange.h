//
// Created by Thomas on 2018-01-15.
//

#ifndef MATHMODELS_STOCKVALUECHANGE_H
#define MATHMODELS_STOCKVALUECHANGE_H


#include <vector>
#include <chrono>
#include <random>

class StockValueChange {
private:
    std::vector<double> currencyValues;
public:
    explicit StockValueChange(const std::vector<double> &currencyValues);

    const std::vector<double> &getCurrencyValues() const;

public:
    double generateKsi();

    std::vector<double> calculateStockValue(double startingStockValue);
};


#endif //MATHMODELS_STOCKVALUECHANGE_H
