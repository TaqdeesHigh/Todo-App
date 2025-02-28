#include "Date.h"

Date::Date() : year(0), month(0), day(0) {}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

bool Date::isValid() const {
    if (year < 2000 || month < 1 || month > 12 || day < 1) return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
        daysInMonth[2] = 29;

    return day <= daysInMonth[month];
}

std::string Date::toString() const {
    if (year == 0 || month == 0 || day == 0) return "No due date";
    std::stringstream ss;
    ss << year << "-" << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;
    return ss.str();
}

Date Date::fromString(const std::string& dateStr) {
    Date date;
    if (dateStr == "No due date") return date;

    std::string tempStr = dateStr;
    std::replace(tempStr.begin(), tempStr.end(), '-', ' ');
    std::stringstream ss(tempStr);
    ss >> date.year >> date.month >> date.day;
    return date;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}