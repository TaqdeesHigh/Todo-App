#include "Priority.h"

std::string priorityToString(const Priority& p) {
    switch (p) {
    case Priority::LOW: return "Low";
    case Priority::MEDIUM: return "Medium";
    case Priority::HIGH: return "High";
    default: return "Unknown";
    }
}

Priority stringToPriority(const std::string& str) {
    if (str == "Low") return Priority::LOW;
    if (str == "High") return Priority::HIGH;
    return Priority::MEDIUM;
}