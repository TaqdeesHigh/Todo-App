#include "TodoList.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

TodoList::TodoList(const std::string& file) : filename(file) {
}

void TodoList::addTask(const Task& task) {
    tasks.push_back(task);
    std::cout << "Task added successfully!" << std::endl;
}

void TodoList::viewTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks available." << std::endl;
        return;
    }

    std::cout << "\n======================= TO-DO LIST =======================\n";
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(30) << "Description"
        << std::setw(10) << "Status"
        << std::setw(10) << "Priority"
        << std::setw(15) << "Category"
        << "Due Date" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << std::setw(5) << i + 1
            << std::setw(30) << (tasks[i].description.length() > 25 ?
                tasks[i].description.substr(0, 22) + "..." :
                tasks[i].description)
            << std::setw(10) << (tasks[i].completed ? "Completed" : "Pending")
            << std::setw(10) << priorityToString(tasks[i].priority)
            << std::setw(15) << tasks[i].category
            << tasks[i].dueDate.toString() << std::endl;
    }
    std::cout << "===========================================================\n";
}

void TodoList::markCompleted(size_t index) {
    if (index >= 1 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        std::cout << "Task marked as completed!" << std::endl;
    }
    else {
        std::cout << "Invalid task number!" << std::endl;
    }
}

void TodoList::deleteTask(size_t index) {
    if (index >= 1 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        std::cout << "Task deleted successfully!" << std::endl;
    }
    else {
        std::cout << "Invalid task number!" << std::endl;
    }
}

void TodoList::searchTasks(const std::string& query) const {
    std::vector<size_t> results;

    for (size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].description.find(query) != std::string::npos ||
            tasks[i].category.find(query) != std::string::npos) {
            results.push_back(i);
        }
    }

    if (results.empty()) {
        std::cout << "No matching tasks found." << std::endl;
        return;
    }

    std::cout << "\n================= SEARCH RESULTS ==================\n";
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(30) << "Description"
        << std::setw(10) << "Status"
        << std::setw(10) << "Priority"
        << std::setw(15) << "Category"
        << "Due Date" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (size_t idx : results) {
        std::cout << std::setw(5) << idx + 1
            << std::setw(30) << (tasks[idx].description.length() > 25 ?
                tasks[idx].description.substr(0, 22) + "..." :
                tasks[idx].description)
            << std::setw(10) << (tasks[idx].completed ? "Completed" : "Pending")
            << std::setw(10) << priorityToString(tasks[idx].priority)
            << std::setw(15) << tasks[idx].category
            << tasks[idx].dueDate.toString() << std::endl;
    }
    std::cout << "===================================================\n";
}

void TodoList::sortByDueDate() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.dueDate.year == 0 && b.dueDate.year == 0) return false;
        if (a.dueDate.year == 0) return false;
        if (b.dueDate.year == 0) return true;
        return a.dueDate < b.dueDate;
        });
    std::cout << "Tasks sorted by due date!" << std::endl;
}

void TodoList::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return static_cast<int>(a.priority) > static_cast<int>(b.priority);
        });
    std::cout << "Tasks sorted by priority!" << std::endl;
}

void TodoList::saveToFile() const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (const Task& task : tasks) {
        file << task.description << "\n"
            << task.category << "\n"
            << (task.completed ? "1" : "0") << "\n"
            << priorityToString(task.priority) << "\n"
            << task.dueDate.toString() << "\n";
    }

    std::cout << "Tasks saved to " << filename << " successfully!" << std::endl;
}

void TodoList::loadFromFile() {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "No saved tasks found or unable to open file." << std::endl;
        return;
    }

    tasks.clear();
    std::string description, category, completed, priority, dueDate;

    while (std::getline(file, description)) {
        std::getline(file, category);
        std::getline(file, completed);
        std::getline(file, priority);
        std::getline(file, dueDate);

        Task task(description, category, stringToPriority(priority), Date::fromString(dueDate));
        task.completed = (completed == "1");
        tasks.push_back(task);
    }

    std::cout << "Loaded " << tasks.size() << " tasks from " << filename << "!" << std::endl;
}

void TodoList::viewStats() const {
    if (tasks.empty()) {
        std::cout << "No tasks available." << std::endl;
        return;
    }

    size_t completed = 0;
    size_t highPriority = 0;
    size_t mediumPriority = 0;
    size_t lowPriority = 0;
    std::map<std::string, size_t> categoryCount;

    for (const Task& task : tasks) {
        if (task.completed) completed++;

        switch (task.priority) {
        case Priority::HIGH: highPriority++; break;
        case Priority::MEDIUM: mediumPriority++; break;
        case Priority::LOW: lowPriority++; break;
        }

        categoryCount[task.category]++;
    }

    std::cout << "\n============= TASK STATISTICS =============\n";
    std::cout << "Total tasks: " << tasks.size() << std::endl;
    std::cout << "Completed: " << completed << " ("
        << (tasks.size() > 0 ? completed * 100 / tasks.size() : 0) << "%)" << std::endl;
    std::cout << "Pending: " << tasks.size() - completed << " ("
        << (tasks.size() > 0 ? (tasks.size() - completed) * 100 / tasks.size() : 0) << "%)" << std::endl;

    std::cout << "\nPriority distribution:" << std::endl;
    std::cout << "High: " << highPriority << std::endl;
    std::cout << "Medium: " << mediumPriority << std::endl;
    std::cout << "Low: " << lowPriority << std::endl;

    std::cout << "\nCategories:" << std::endl;
    for (const auto& pair : categoryCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "===========================================\n";
}