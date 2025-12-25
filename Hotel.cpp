#include "Hotel.h"
#include "Room.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void Hotel::addRoom(Room* room) {
    if (room) {
        roomNumbers.insert(room->getRoomNumber());
        rooms.push_back(room);
    }
}

bool Hotel::isRoomNumberExists(int number) const {
    return roomNumbers.find(number) != roomNumbers.end();
}

void Hotel::displayAllRooms() const {
    if (rooms.empty()) {
        std::cout << "В гостинице нет номеров.\n";
        return;
    }

    std::cout << "\n=== СПИСОК НОМЕРОВ ГОСТИНИЦЫ ===\n";
    for (size_t i = 0; i < rooms.size(); ++i) {
        std::cout << "\nНомер " << i + 1 << ":\n";
        rooms[i]->displayInfo();
        std::cout << "------------------------------\n";
    }
}

double Hotel::calculateAveragePrice() const {
    if (rooms.empty()) {
        throw std::runtime_error("Невозможно рассчитать среднюю стоимость: в гостинице нет номеров");
    }
    double total = 0.0;
    for (const auto& room : rooms) {
        total += room->calculatePrice();
    }
    return total / rooms.size();
}

const std::vector<Room*>& Hotel::getRooms() const {
    return rooms;
}

void Hotel::removeRoomAt(int index) {
    if (index >= 0 && index < (int)rooms.size()) {
        roomNumbers.erase(rooms[index]->getRoomNumber());
        delete rooms[index];
        rooms.erase(rooms.begin() + index);
    }
}

void Hotel::clearRooms() {
    for (auto room : rooms) {
        delete room;
    }
    rooms.clear();
    roomNumbers.clear();
}

void Hotel::sortByRoomNumber() {
    std::sort(rooms.begin(), rooms.end(),
        [](const Room* a, const Room* b) {
            return a->getRoomNumber() < b->getRoomNumber();
        });
}

void Hotel::sortByBasePrice() {
    std::sort(rooms.begin(), rooms.end(),
        [](const Room* a, const Room* b) {
            return a->getBasePrice() < b->getBasePrice();
        });
}

void Hotel::sortByFinalPrice() {
    std::sort(rooms.begin(), rooms.end(),
        [](const Room* a, const Room* b) {
            return a->calculatePrice() < b->calculatePrice();
        });
}

int Hotel::getRoomCount() const {
    return rooms.size();
}

Hotel::~Hotel() {
    clearRooms();
}

void Hotel::sortByRoomNumber(bool ascending) {
    std::sort(rooms.begin(), rooms.end(),
        [ascending](Room* a, Room* b) {
            return ascending
                ? a->getRoomNumber() < b->getRoomNumber()
                : a->getRoomNumber() > b->getRoomNumber();
        });
}

void Hotel::sortByBasePrice(bool ascending) {
    std::sort(rooms.begin(), rooms.end(),
        [ascending](Room* a, Room* b) {
            return ascending
                ? a->getBasePrice() < b->getBasePrice()
                : a->getBasePrice() > b->getBasePrice();
        });
}

void Hotel::sortByFinalPrice(bool ascending) {
    std::sort(rooms.begin(), rooms.end(),
        [ascending](Room* a, Room* b) {
            return ascending
                ? a->calculatePrice() < b->calculatePrice()
                : a->calculatePrice() > b->calculatePrice();
        });
}
