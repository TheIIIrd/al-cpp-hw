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

#include "binstree.hpp"
#include <iostream>

int main() {
  BSTree<int> test;
  char _ANS;

  while (_ANS != '0') {
    std::cout << "--- [B] BINSTREE TEST ---" << std::endl;
    std::cout
        << "1: add\n2: print\n3: find\n4: remove\n5: load\n6: save\n0: exit"
        << std::endl;

    std::cout << "[U] >>> ";
    std::cin >> _ANS;

    switch (_ANS) {
    case '1': {
      int _TMP;
      std::cout << "[1] Value >>> ";
      std::cin >> _TMP;

      test.add_element(_TMP);

      std::cout << std::endl;
      break;
    }

    case '2': {
      std::cout << "[2] Tree" << std::endl;
      test.print_tree();

      std::cout << std::endl;
      break;
    }

    case '3': {
      int _TMP;
      std::cout << "[3] Value >>> ";
      std::cin >> _TMP;

      if (test.find_element(_TMP))
        std::cout << "[+] We found it!" << std::endl;
      else
        std::cout << "[-] There is no " << _TMP << std::endl;

      std::cout << std::endl;
      break;
    }

    case '4': {
      int _TMP;
      std::cout << "[4] Value >>> ";
      std::cin >> _TMP;

      if (test.delete_element(_TMP))
        std::cout << "[+] Deleated" << std::endl;
      else
        std::cout << "[-] There is no " << _TMP << std::endl;

      std::cout << std::endl;
      break;
    }

    case '5': {
      std::string _PATH;
      std::cout << "[5] path >>>";
      std::cin >> _PATH;

      test.load_from_file(_PATH);

      std::cout << std::endl;
      break;
    }

    case '6': {
      std::string _PATH;
      std::cout << "[5] path >>>";
      std::cin >> _PATH;

      test.save_to_file(_PATH);

      std::cout << std::endl;
      break;
    }

    default:
      return 0;
    }
  }
  return 0;
}
