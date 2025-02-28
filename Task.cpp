#include "Task.h"

Task::Task(const std::string& desc, const std::string& cat,
    Priority p, const Date& date)
    : description(desc), category(cat), completed(false), priority(p), dueDate(date) {
}