#pragma once

#include "dungeon.h"
#include <stdexcept>

Room* NextRoom(Room* current_room, std::vector<Door*>& doors, std::vector<std::string>& keys,
               std::vector<Room*>& checked_rooms) {
    checked_rooms.push_back(current_room);
    Room* res = nullptr;
    if (current_room->IsFinal()) {
        return current_room;
    } else {
        for (size_t i = 0; i < current_room->NumKeys(); i++) {
            if (std::find(keys.begin(), keys.end(), current_room->GetKey(i)) == keys.end()) {
                keys.push_back(current_room->GetKey(i));
            }
        }
        for (size_t i = 0; i < current_room->NumDoors(); i++) {
            Door* tmp = current_room->GetDoor(i);
            if (tmp->IsOpen()) {
                if (std::find(checked_rooms.begin(), checked_rooms.end(), tmp->GoThrough()) ==
                    checked_rooms.end()) {
                    res = NextRoom(tmp->GoThrough(), doors, keys, checked_rooms);
                    if (res != nullptr) {
                        return res;
                    }
                }
            } else {
                for (auto key : keys) {
                    if (tmp->TryOpen(key)) {
                        if (std::find(checked_rooms.begin(), checked_rooms.end(),
                                      tmp->GoThrough()) == checked_rooms.end()) {
                            res = NextRoom(tmp->GoThrough(), doors, keys, checked_rooms);
                            if (res != nullptr) {
                                return res;
                            }
                        }
                        break;
                    }
                }
                if (!tmp->IsOpen()) {
                    doors.push_back(tmp);
                }
            }
        }
    }
    return res;
}

Room* FindFinalRoom(Room* starting_room) {
    Room* room_end = nullptr;
    std::vector<Door*> doors;
    std::vector<std::string> keys;
    std::vector<Room*> checked_rooms;
    room_end = NextRoom(starting_room, doors, keys, checked_rooms);
    if (room_end != nullptr) {
        return room_end;
    }
    checked_rooms.resize(0);
    while (room_end == nullptr) {
        size_t open = 0;
        size_t count = keys.size();
        for (auto& x : doors) {
            if (x->IsOpen()) {
                open++;
                continue;
            }
            for (auto key : keys) {
                if (x->TryOpen(key)) {
                    room_end = NextRoom(x->GoThrough(), doors, keys, checked_rooms);
                    if (room_end != nullptr) {
                        return room_end;
                    }
                    checked_rooms.resize(0);
                    break;
                } else {
                    count--;
                }
            }
        }

        if (open == doors.size() || count == 0) {
            break;
        }
    }

    return room_end;
}