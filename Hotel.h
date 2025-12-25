#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <set>
#include <stdexcept>

class Room; 

class Hotel {
private:
    std::vector<Room*> rooms;
    std::set<int> roomNumbers;


public:
    void addRoom(Room* room);
    bool isRoomNumberExists(int number) const;
    void displayAllRooms() const;
    double calculateAveragePrice() const;
    void sortByRoomNumber(bool ascending);
    void sortByBasePrice(bool ascending);
    void sortByFinalPrice(bool ascending);

    const std::vector<Room*>& getRooms() const;
    void removeRoomAt(int index);
    void clearRooms();
    void sortByRoomNumber();
    void sortByBasePrice();
    void sortByFinalPrice();
    int getRoomCount() const;
    ~Hotel();
};

#endif