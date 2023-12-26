#include <bits/stdc++.h>
using namespace std;

class Room
{
public:
    int roomNumber;
    bool isOccupied;
    double rate;

    Room(int number, double rate) : roomNumber(number), isOccupied(false), rate(rate) {}
};

class Reservation
{
public:
    int reservationNumber;
    int roomNumber;
    string guestName;
    int duration;

    Reservation(int resNumber, int roomNumber, const string &name, int duration)
        : reservationNumber(resNumber), roomNumber(roomNumber), guestName(name), duration(duration) {}
};

class Hotel
{
private:
    vector<Room> rooms;
    vector<Reservation> reservations;
    static int lastReservationNumber;

public:
    Hotel()
    {
        for (int i = 1; i <= 10; ++i)
        {
            rooms.push_back(Room(i, 100.0 * i));
        }
    }

    void displayAvailableRooms()
    {
        cout << "Available Rooms:\n";
        cout << "-----------------\n";
        for (const Room &room : rooms)
        {
            if (!room.isOccupied)
            {
                cout << "Room " << room.roomNumber << " ($" << room.rate << " per day)\n";
            }
        }
        cout << "-----------------\n";
    }

    void makeReservation()
    {
        int roomNumber, duration;
        string guestName;

        cin.ignore();
        cout << "Enter guest name: ";
        getline(cin, guestName);
        displayAvailableRooms();
        cout << "Enter room number for reservation: ";

        while (!(cin >> roomNumber) || roomNumber < 1 || roomNumber > 10 || rooms[roomNumber - 1].isOccupied)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid room number or room is already occupied. Please enter a valid room number: ";
        }

        cout << "Enter duration of stay (in days): ";
        while (!(cin >> duration) || duration <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid duration. Please enter a positive integer: ";
        }

        Room &selectedRoom = rooms[roomNumber - 1];
        int reservationNumber = ++lastReservationNumber;
        selectedRoom.isOccupied = true;
        reservations.push_back(Reservation(reservationNumber, roomNumber, guestName, duration));
        cout << "Reservation successful! Reservation number: " << reservationNumber << "\n";
    }

    void displayReservations()
    {
        cout << "Reservations:\n";
        cout << "-----------------\n";
        for (const Reservation &reservation : reservations)
        {
            cout << "Reservation Number: " << reservation.reservationNumber << "\n";
            cout << "Guest Name: " << reservation.guestName << "\n";
            cout << "Room Number: " << reservation.roomNumber << "\n";
            cout << "Duration: " << reservation.duration << " days\n";
            cout << "-----------------\n";
        }
    }

    void cancelReservation()
    {
        int reservationNumber;
        cout << "Enter the reservation number to cancel: ";
        while (!(cin >> reservationNumber) || reservationNumber <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid reservation number. Please enter a positive integer: ";
        }

        auto reservationIter = find_if(reservations.begin(), reservations.end(),
                                       [reservationNumber](const Reservation &r)
                                       { return r.reservationNumber == reservationNumber; });

        if (reservationIter != reservations.end())
        {
            Room &canceledRoom = rooms[reservationIter->roomNumber - 1];
            canceledRoom.isOccupied = false;
            reservations.erase(reservationIter);
            cout << "Reservation canceled successfully.\n";
        }
        else
        {
            cout << "Reservation not found. Please enter a valid reservation number.\n";
        }
    }
};

int Hotel::lastReservationNumber = 0;

int main()
{
    Hotel hotel;

    int choice;
    do
    {
        cout << "Hotel Management System\n";
        cout << "1. Display available rooms\n";
        cout << "2. Make a reservation\n";
        cout << "3. Display reservations\n";
        cout << "4. Cancel a reservation\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        switch (choice)
        {
        case 1:
            hotel.displayAvailableRooms();
            system("PAUSE");
            break;

        case 2:
            hotel.makeReservation();
            system("PAUSE");
            system("CLS");
            break;

        case 3:
            hotel.displayReservations();
            system("PAUSE");
            break;

        case 4:
            hotel.cancelReservation();
            system("PAUSE");
            system("CLS");
            break;

        case 0:
            cout << "Thanks for staying. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}