#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "TodoList.h"

class UserInterface {
public:
    static void displayMenu();
    static bool handleMenuChoice(int choice, TodoList& todoList);

private:
    static void addTaskDialog(TodoList& todoList);
    static void markCompletedDialog(TodoList& todoList);
    static void deleteTaskDialog(TodoList& todoList);
    static void searchTasksDialog(TodoList& todoList);
};

#endif