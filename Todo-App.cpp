#include <iostream>
#include <limits>
#include "TodoList.h"
#include "UserInterface.h"

int main() {
    TodoList todoList;
    int choice;

    std::cout << "Welcome to the Enhanced To-Do List Manager!" << std::endl;

    todoList.loadFromFile();

    while (true) {
        UserInterface::displayMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (UserInterface::handleMenuChoice(choice, todoList)) {
            return 0;
        }
    }

    return 0;
}