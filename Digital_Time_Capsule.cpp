#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "utilities.h"

using namespace std;

class DateTime {
private:
    int year, month, day, hour, minute;

public:
    DateTime() {
        time_t now = time(nullptr);
        tm* currentTime = localtime(&now);
        year = currentTime->tm_year + 1900;
        month = currentTime->tm_mon + 1;
        day = currentTime->tm_mday;
        hour = currentTime->tm_hour;
        minute = currentTime->tm_min;
    }

    DateTime(int y, int m, int d, int h, int min) {
        year = y;
        month = m;
        day = d;
        hour = h;
        minute = min;
    }

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }

    bool isValid() const {
        if (month < 1 || month > 12 || hour < 0 || hour > 23 ||
            minute < 0 || minute > 59)
            return false;

        int daysInMonth[] = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };

        bool leapYear = (year % 400 == 0) ||
                        (year % 4 == 0 && year % 100 != 0);

        if (leapYear && month == 2)
            daysInMonth[1] = 29;

        return day >= 1 && day <= daysInMonth[month - 1];
    }

    time_t toTimeT() const {
        tm timeInfo = {};
        timeInfo.tm_year = year - 1900;
        timeInfo.tm_mon = month - 1;
        timeInfo.tm_mday = day;
        timeInfo.tm_hour = hour;
        timeInfo.tm_min = minute;
        timeInfo.tm_sec = 0;
        return mktime(&timeInfo);
    }

    bool isBefore(const DateTime& other) const {
        return toTimeT() < other.toTimeT();
    }

    long long getRemainingSeconds() const {
        DateTime currentDate;
        time_t currentTime = currentDate.toTimeT();
        time_t targetTime = toTimeT();

        if (targetTime <= currentTime)
            return 0;

        return static_cast<long long>(
            difftime(targetTime, currentTime)
        );
    }

    void display() const {
        cout << setfill('0')
             << year << "-" << setw(2) << month << "-"
             << setw(2) << day << " "
             << setw(2) << hour << ":" << setw(2) << minute
             << setfill(' ') << endl;
    }
};

class TimeCapsule {
private:
    string capsuleID;
    string ownerName;
    string message;
    DateTime creationDate;
    DateTime unlockDate;
    bool locked;

public:
    TimeCapsule(string id, string owner, string msg, DateTime unlock)
        : capsuleID(id), ownerName(owner), message(msg),
          unlockDate(unlock), locked(true) {
        creationDate = DateTime();
    }

    string getCapsuleID() const { return capsuleID; }
    string getOwnerName() const { return ownerName; }
    string getMessage() const { return message; }
    DateTime getCreationDate() const { return creationDate; }
    DateTime getUnlockDate() const { return unlockDate; }
    bool isLocked() const { return locked; }

    void checkAndUnlock() {
        DateTime currentDate;
        locked = currentDate.isBefore(unlockDate);
    }

    long long getRemainingSeconds() const {
        return unlockDate.getRemainingSeconds();
    }

    void displayRemainingTime() const {
        long long totalSeconds = getRemainingSeconds();

        if (totalSeconds == 0) {
            cout << "Time Left  : Ready to unlock!" << endl;
            return;
        }

        long long days = totalSeconds / (24 * 60 * 60);
        totalSeconds %= (24 * 60 * 60);
        long long hours = totalSeconds / (60 * 60);
        totalSeconds %= (60 * 60);
        long long minutes = totalSeconds / 60;
        long long seconds = totalSeconds % 60;

        cout << "Time Left  : " << days << " days, "
             << hours << " hours, " << minutes << " minutes, "
             << seconds << " seconds" << endl;
    }

    void displayCapsule() const {
        cout << "\n====================================\n";
        cout << "       DIGITAL TIME CAPSULE\n";
        cout << "====================================\n";
        cout << "Capsule ID : " << capsuleID << endl;
        cout << "Owner      : " << ownerName << endl;

        cout << "Created    : ";
        creationDate.display();

        cout << "Unlock Date: ";
        unlockDate.display();

        cout << "Status     : "
             << (locked ? "LOCKED" : "UNLOCKED") << endl;

        if (locked) {
            displayRemainingTime();
            cout << "Message    : [LOCKED]" << endl;
        } else {
            cout << "Time Left  : UNLOCKED" << endl;
            cout << "Message    : " << message << endl;
        }

        cout << "====================================\n";
    }
};

int main() {

    // Enabling Virtual Terminal Proccessing
    sys::EnableVirtualTerminalProcessing();


    string name, message;
    int year, month, day, hour, minute;

    cout << color::b_yellow;
    cout << "====================================\n";
    cout << "       CREATE DIGITAL CAPSULE\n";
    cout << "====================================\n";
    cout << color::reset;

    sys::type_write("\nEnter your name: ");
    getline(cin, name);

    sys::type_write("Enter your message: ");
    getline(cin, message);

    cout << "\nEnter unlock date and time\n";
    cout << "Year: ";
    cin >> year;
    cout << "Month (1-12): ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    cout << "Hour (0-23): ";
    cin >> hour;
    cout << "Minute (0-59): ";
    cin >> minute;

    DateTime unlockDate(year, month, day, hour, minute);

    sys::playspinner(3, "Checking the Specifications");

    if (!unlockDate.isValid()) {
        cout << color::red << "\nERROR: Invalid date or time!\n" << color::reset;
        return 0;
    }

    static int capsuleNumber = 1;
    string capsuleID = "TC00" + to_string(capsuleNumber);

    TimeCapsule capsule(capsuleID, name, message, unlockDate);

    capsule.checkAndUnlock();

    cout << "\n" << color::green << style::bold << style::blink;
    design::draw_header("CAPSULE CREATED SUCCESSFULLY!", "=");
    cout << "\n\n" << color::reset;
    capsule.displayCapsule();

    sys::pause();

    return 0;
}
