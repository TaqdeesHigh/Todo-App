#ifndef PRIORITY_H
#define PRIORITY_H

#include <string>

enum class Priority { LOW, MEDIUM, HIGH };

std::string priorityToString(const Priority& p);
Priority stringToPriority(const std::string& str);

#endif