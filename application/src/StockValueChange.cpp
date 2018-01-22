//
// Created by Thomas on 2018-01-18.
//

#include "StockValueChange.h"

StockValueChange::StockValueChange(const std::vector<double> &stockValue) : currencyValues(stockValue) {}

const std::vector<double> &StockValueChange::getCurrencyValues() const {
    return currencyValues;
}

double StockValueChange::generateKsi() {
    unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> ksi_dist(1.0, 9999.0);
    double ksi = ksi_dist(generator);
    double percentage = 0;
    if (ksi >= 1.0 && ksi < 2.0) {
        std::uniform_real_distribution<double> percentage_dist(15.1, 30.0);
        percentage = -(percentage_dist(generator));
    } else if (ksi >= 2.0 && ksi < 150.0) {
        std::uniform_real_distribution<double> percentage_dist(8.1, 15.0);
        percentage = -(percentage_dist(generator));
    } else if (ksi >= 150.0 && ksi < 1000.0) {
        std::uniform_real_distribution<double> percentage_dist(3.1, 8.0);
        percentage = -(percentage_dist(generator));
    } else if (ksi >= 1000.0 && ksi < 5000.0) {
        std::uniform_real_distribution<double> percentage_dist(1.0, 3.0);
        percentage = -(percentage_dist(generator));
    } else if (ksi >= 5000.0 && ksi < 9000.0) {
        std::uniform_real_distribution<double> percentage_dist(1.0, 3.0);
        percentage = percentage_dist(generator);
    } else if (ksi >= 9000.0 && ksi < 9850.0) {
        std::uniform_real_distribution<double> percentage_dist(3.1, 8.0);
        percentage = percentage_dist(generator);
    } else if (ksi >= 9850.0 && ksi < 9999.0) {
        std::uniform_real_distribution<double> percentage_dist(8.1, 15.0);
        percentage = percentage_dist(generator);
    } else if (ksi >= 9998.0 && ksi < 9999.0) {
        std::uniform_real_distribution<double> percentage_dist(15.1, 30.0);
        percentage = percentage_dist(generator);
    }

    return percentage;
}

std::vector<double> StockValueChange::calculateStockValue(double startingStockValue) {
    std::vector<double> stockValues = {startingStockValue};
    double previousValue = this->getCurrencyValues().front();
    double percentage = 0;

    for (auto &value : getCurrencyValues()) {
        sleep(1);
        if (previousValue > value) {
            percentage = generateKsi();
            stockValues.push_back(
                    round((((stockValues.back() / value) * ((percentage + 99.9) / 100)) * value) * 1000) / 1000);
            previousValue = value;
        } else if (previousValue < value) {
            percentage = generateKsi();
            stockValues.push_back(
                    round((((stockValues.back() / value) * ((percentage + 100.1) / 100)) * value) * 1000) / 1000);
            previousValue = value;
        } else {
            percentage = generateKsi();
            stockValues.push_back(
                    round((((stockValues.back() / value) * ((percentage + 100) / 100)) * value) * 1000) / 1000);
            previousValue = value;
        }
    }

    return stockValues;
}