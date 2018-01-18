//
// Created by Thomas on 2018-01-15.
//


// DO POPRAWYYYYYYY

#include "../headers/StockValueChange.h"

StockValueChange::StockValueChange(const std::vector<double> &stockValue) : currencyValues(stockValue) {}

const std::vector<double> &StockValueChange::getCurrencyValues() const {
    return currencyValues;
}

double StockValueChange::generateKsi() {
    unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> ksi_dist(0.0, 10000.0);
    double ksi = ksi_dist(generator);
    double percentage = 0;
    if (ksi >= 1000.0 && ksi <= 9000.0) {
        std::uniform_real_distribution<double> percentage_dist(0.0, 3);
        percentage = percentage_dist(generator);
    } else if ((ksi >= 150.0 && ksi < 1000.0) || (ksi <= 9850.0 && ksi > 9000.0)) {
        std::uniform_real_distribution<double> percentage_dist(3.1, 8.0);
        percentage = percentage_dist(generator);
    } else if ((ksi >= 1.0 && ksi < 150.0) || (ksi <= 9999.0 && ksi > 9850.0)) {
        std::uniform_real_distribution<double> percentage_dist(8.1, 15.0);
        percentage = percentage_dist(generator);
    } else if ((ksi >= 0.0 && ksi < 1.0) || (ksi <= 10000.0 && ksi > 9999.0)) {
        std::uniform_real_distribution<double> percentage_dist(15.1, 30.0);
        percentage = percentage_dist(generator);
    }

    std::uniform_int_distribution<int> sign_dist(0, 1);
    double sign = sign_dist(generator);

    if (sign == 1) {
        return (-percentage);
    } else {
        return percentage;
    }
}

std::vector<double> StockValueChange::calculateStockValue(double startingStockValue) {
    std::vector<double> stockValues = {startingStockValue};
    double previousValue = this->getCurrencyValues().front();
    double percentage = 0;

    for (auto &value : getCurrencyValues()) {
        if (previousValue > value) {
            percentage = generateKsi();
            stockValues.push_back(
                    round((((stockValues.back() / value) * ((percentage + 100.1) / 100)) * value) * 1000) / 1000);
        } else if (previousValue < value) {
            percentage = generateKsi();
            stockValues.push_back(
                    round((((stockValues.back() / value) * ((percentage + 99.1) / 100)) * value) * 1000) / 1000);
        } else {
            percentage = generateKsi();
            stockValues.push_back(
                    round((((stockValues.back() / value) * ((percentage + 100) / 100)) * value) * 1000) / 1000);
        }
    }

    return stockValues;
}


