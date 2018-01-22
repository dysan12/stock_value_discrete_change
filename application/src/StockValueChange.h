//
// Created by Thomas on 2018-01-18.
//

#ifndef AET_STOCKVALUECHANGE_H
#define AET_STOCKVALUECHANGE_H


#include <vector>
#include <chrono>
#include <random>
#include <zconf.h>

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


#endif //AET_STOCKVALUECHANGE_H