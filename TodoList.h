#ifndef TODOLIST_H
#define TODOLIST_H

#include <vector>
#include <string>
#include <map>
#include "Task.h"

class TodoList {
private:
    std::vector<Task> tasks;
    std::string filename;

public:
    TodoList(const std::string& file = "todo_list.txt");

    void addTask(const Task& task);
    void viewTasks() const;
    void markCompleted(size_t index);
    void deleteTask(size_t index);
    void searchTasks(const std::string& query) const;
    void sortByDueDate();
    void sortByPriority();
    void saveToFile() const;
    void loadFromFile();
    void viewStats() const;
};

#endif