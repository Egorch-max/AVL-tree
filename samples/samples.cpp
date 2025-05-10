#include "AVL_Tree.h"
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer()
{
    cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() 
{
    cout << "\n=== AVL Tree Manager ===" << endl;

    cout << "1. Добавить элементы" << endl;

    cout << "2. Удалить элементы" << endl;

    cout << "3. Показать дерево" << endl;

    cout << "4. Выход" << endl;

    cout << "Выберите действие: ";
}

void insertElements(AVL_tree& tree) 
{
    cout << "\nВведите элементы для добавления (0 для завершения):" << endl;

    int value;
    while (true)
    {
        cout << "> ";

        if (!(cin >> value)) 
        {
            cout << "Ошибка ввода. Пожалуйста, введите целое число." << endl;

            clearInputBuffer();

            continue;
        }
        if (value == 0) break;

        try 
        {
            tree.insert(value);

            cout << "Элемент " << value << " успешно добавлен." << endl;
        }
        catch (const logic_error& e) 
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

void removeElements(AVL_tree& tree)
{
    cout << "\nВведите элементы для удаления (0 для завершения):" << endl;

    int value;

    while (true)
    {
        cout << "> ";

        if (!(cin >> value)) 
        {
            cout << "Ошибка ввода. Пожалуйста, введите целое число." << endl;

            clearInputBuffer();

            continue;
        }
        if (value == 0) break;

        try {
            tree.erase(value);

            cout << "Элемент " << value << " успешно удален." << endl;
        }
        catch (const logic_error& e)
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

void printTree(const AVL_tree& tree) 
{
    cout << "\nТекущее состояние AVL-дерева:" << endl;

    cout << "-------------------------" << endl;

    tree.print();

    cout << "-------------------------" << endl;
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    AVL_tree tree;

    int choice;

    do
    {
        displayMenu();

        cin >> choice;

        clearInputBuffer();


        switch (choice) 
        {
        case 1:

            insertElements(tree);

            break;

        case 2:

            removeElements(tree);

            break;

        case 3:

            printTree(tree);

            break;

        case 4:

            cout << "Выход из программы..." << endl;

            break;

        default:

            cout << "Неверный выбор. Пожалуйста, выберите от 1 до 4." << endl;
        }

    } while (choice != 4);

    return 0;
}