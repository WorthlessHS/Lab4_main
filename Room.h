#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <memory>
#include <iostream>
#include <iomanip>


class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double applyDiscount(double basePrice) const = 0;
    virtual bool isNoDiscount() const { return false; }
    virtual double getDiscountPercentage() const { return 0.0; }
};

class NoDiscount : public PricingStrategy {
public:
    double applyDiscount(double basePrice) const override;
    bool isNoDiscount() const override;
};

class PercentageDiscount : public PricingStrategy {
private:
    double discountPercentage;
public:
    PercentageDiscount(double percentage);
    double applyDiscount(double basePrice) const override;
    double getDiscountPercentage() const override;
};


class Room {
protected:
    int roomNumber;
    double basePrice;
    std::unique_ptr<PricingStrategy> discountStrategy;

public:
    Room(int num, double base, std::unique_ptr<PricingStrategy> strategy);
    virtual ~Room() = default;

    virtual double calculatePrice() const;
    virtual void displayInfo() const = 0;
    virtual std::string getRoomType() const = 0;

    bool hasNoDiscount() const;
    int getRoomNumber() const;
    double getBasePrice() const;
    double getDiscountPercentage() const;
    PricingStrategy* getStrategy() const;
};

class StandardRoom : public Room {
public:
    StandardRoom(int num, double base, std::unique_ptr<PricingStrategy> strategy);
    void displayInfo() const override;
    std::string getRoomType() const override;
};

class LuxuryRoom : public Room {
public:
    LuxuryRoom(int num, double base, std::unique_ptr<PricingStrategy> strategy);
    void displayInfo() const override;
    std::string getRoomType() const override;
};

#endif