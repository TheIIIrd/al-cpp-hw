/*
Домашние задание №2-3

Необходимо реализовать класс BSTree (двоичное дерево поиска).
За основу для реализации элементов дерева написать структуру Node.
Структура должна содержать указатели на левый и правый элемент
дерева, поле данных типа int, а также опционально указатель на
предыдущий элемент.

Класс должен содержать указатель на корень с модификатором доступа
private, остальные методы и поля могут быть с модификатором доступа
public (при защите необходимо будет обосновать).

Класс должен содержать два конструктора:
BSTree(); // конструктор по умолчанию.
BSTree(initializer_list<int> list); // конструктор с параметром.

Класс должен содержать следующие функции:
bool add_element(int value); // функция добавления
bool delete_element(int value); // функция удаления
bool find_element(int value); // функция поиска элемента
void print(); // функция вывода дерева в консоль
bool save_to_file(const std::string& path); // функция сохранения в файл
bool load_from_file(const std::string& path); // функция загрузки из файла
~BSTree(); //деструктор
*/

#include <iostream>
#include "binstree.hpp"

int main() {
  BSTree<int> test;
  test.add_element(8);
  test.add_element(4);
  test.add_element(12);
  test.add_element(2);
  test.add_element(5);
  test.add_element(9);
  test.add_element(14);
  test.add_element(3);
  test.add_element(7);
  test.add_element(10);
  test.add_element(15);
  test.add_element(16);
  test.add_element(6);
  test.add_element(11);
  test.add_element(13);
  test.add_element(1);

  test.print_tree();

  if (test.find_element(10))
    std::cout << std::endl << "[+] Element found!" << std::endl;
  else
    std::cout << std::endl << "[-] Element not found!" << std::endl;

  if (test.find_element(6))
    std::cout << std::endl << "[+] Element found!" << std::endl;
  else
    std::cout << std::endl << "[-] Element not found!" << std::endl;

  if (test.find_element(8))
    std::cout << std::endl << "[+] Element found!" << std::endl;
  else
    std::cout << std::endl << "[-] Element not found!" << std::endl;

  if (test.find_element(50))
    std::cout << std::endl << "[+] Element found!" << std::endl;
  else
    std::cout << std::endl << "[-] Element not found!" << std::endl;

  test.delete_element(5);
  test.delete_element(4);

  test.print_tree();

  return 0;
}
