#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

class Date {
public:
    int year;
    int month;
    int day;

    Date();
    Date(int y, int m, int d);

    bool isValid() const;
    std::string toString() const;
    static Date fromString(const std::string& dateStr);
    bool operator<(const Date& other) const;
};

#endif