#include "Room.h"

double NoDiscount::applyDiscount(double basePrice) const {
    return basePrice;
}

bool NoDiscount::isNoDiscount() const {
    return true;
}

PercentageDiscount::PercentageDiscount(double percentage)
    : discountPercentage(percentage) {}

double PercentageDiscount::applyDiscount(double basePrice) const {
    return basePrice * (1.0 - discountPercentage / 100.0);
}

double PercentageDiscount::getDiscountPercentage() const {
    return discountPercentage;
}

Room::Room(int num, double base, std::unique_ptr<PricingStrategy> strategy)
    : roomNumber(num), basePrice(base), discountStrategy(std::move(strategy)) {}

double Room::calculatePrice() const {
    return discountStrategy->applyDiscount(basePrice);
}

bool Room::hasNoDiscount() const {
    return discountStrategy->isNoDiscount();
}

int Room::getRoomNumber() const {
    return roomNumber;
}

double Room::getBasePrice() const {
    return basePrice;
}

double Room::getDiscountPercentage() const {
    return discountStrategy->getDiscountPercentage();
}

PricingStrategy* Room::getStrategy() const {
    return discountStrategy.get();
}

StandardRoom::StandardRoom(int num, double base, std::unique_ptr<PricingStrategy> strategy)
    : Room(num, base, std::move(strategy)) {}

void StandardRoom::displayInfo() const {
    std::cout << "Тип: Стандартный номер\n";
    std::cout << "Номер: " << roomNumber << "\n";
    std::cout << "Базовая стоимость: " << std::fixed << std::setprecision(2) << basePrice << " руб.\n";
    if (!hasNoDiscount()) {
        std::cout << "Стоимость со скидкой: " << std::fixed << std::setprecision(2) << calculatePrice() << " руб.\n";
    }
}

std::string StandardRoom::getRoomType() const {
    return "Standard";
}

LuxuryRoom::LuxuryRoom(int num, double base, std::unique_ptr<PricingStrategy> strategy)
    : Room(num, base, std::move(strategy)) {}

void LuxuryRoom::displayInfo() const {
    std::cout << "Тип: Люкс номер\n";
    std::cout << "Номер: " << roomNumber << "\n";
    std::cout << "Базовая стоимость: " << std::fixed << std::setprecision(2) << basePrice << " руб.\n";
    if (!hasNoDiscount()) {
        std::cout << "Стоимость со скидкой: " << std::fixed << std::setprecision(2) << calculatePrice() << " руб.\n";
    }
}

std::string LuxuryRoom::getRoomType() const {
    return "Luxury";
}   