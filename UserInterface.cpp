#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>

void UserInterface::displayMenu() {
    std::cout << "\n================== MENU ==================\n";
    std::cout << "1. Add a new task\n";
    std::cout << "2. View all tasks\n";
    std::cout << "3. Mark a task as completed\n";
    std::cout << "4. Delete a task\n";
    std::cout << "5. Search tasks\n";
    std::cout << "6. Sort tasks by due date\n";
    std::cout << "7. Sort tasks by priority\n";
    std::cout << "8. Save tasks to file\n";
    std::cout << "9. Load tasks from file\n";
    std::cout << "10. View task statistics\n";
    std::cout << "11. Exit\n";
    std::cout << "==========================================\n";
    std::cout << "Enter your choice (1-11): ";
}

bool UserInterface::handleMenuChoice(int choice, TodoList& todoList) {
    switch (choice) {
    case 1:
        addTaskDialog(todoList);
        break;

    case 2:
        todoList.viewTasks();
        break;

    case 3:
        markCompletedDialog(todoList);
        break;

    case 4:
        deleteTaskDialog(todoList);
        break;

    case 5:
        searchTasksDialog(todoList);
        break;

    case 6:
        todoList.sortByDueDate();
        break;

    case 7:
        todoList.sortByPriority();
        break;

    case 8:
        todoList.saveToFile();
        break;

    case 9:
        todoList.loadFromFile();
        break;

    case 10:
        todoList.viewStats();
        break;

    case 11:
        return true;

    default:
        std::cout << "Invalid choice. Please enter a number between 1 and 11." << std::endl;
    }

    return false;
}

void UserInterface::addTaskDialog(TodoList& todoList) {
    std::string description, category;
    int priorityChoice;

    std::cout << "Enter task description: ";
    std::getline(std::cin, description);

    std::cout << "Enter task category (or leave empty for 'General'): ";
    std::getline(std::cin, category);
    if (category.empty()) category = "General";

    std::cout << "Select priority (1: Low, 2: Medium, 3: High): ";
    std::cin >> priorityChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Priority priority;
    switch (priorityChoice) {
    case 1: priority = Priority::LOW; break;
    case 3: priority = Priority::HIGH; break;
    default: priority = Priority::MEDIUM; break;
    }

    std::string dueDateStr;
    std::cout << "Enter due date (YYYY-MM-DD) or leave empty for no due date: ";
    std::getline(std::cin, dueDateStr);

    Date dueDate;
    if (!dueDateStr.empty()) {
        std::replace(dueDateStr.begin(), dueDateStr.end(), '-', ' ');
        std::stringstream ss(dueDateStr);
        ss >> dueDate.year >> dueDate.month >> dueDate.day;

        if (!dueDate.isValid()) {
            std::cout << "Invalid date format. Using no due date." << std::endl;
            dueDate = Date();
        }
    }

    Task task(description, category, priority, dueDate);
    todoList.addTask(task);
}

void UserInterface::markCompletedDialog(TodoList& todoList) {
    size_t taskIndex;
    std::cout << "Enter task number to mark as completed: ";
    if (std::cin >> taskIndex) {
        todoList.markCompleted(taskIndex);
    }
    else {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void UserInterface::deleteTaskDialog(TodoList& todoList) {
    size_t taskIndex;
    std::cout << "Enter task number to delete: ";
    if (std::cin >> taskIndex) {
        todoList.deleteTask(taskIndex);
    }
    else {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void UserInterface::searchTasksDialog(TodoList& todoList) {
    std::string query;
    std::cout << "Enter search term: ";
    std::getline(std::cin, query);
    todoList.searchTasks(query);
}