#ifndef BINSTREEM_HPP_
#define BINSTREEM_HPP_

#include "binode.hpp"
#include <iostream>
#include <fstream>

template <class T> class BSTree {
private:
  Node<T> *_HEAD; // Узел-корень бинарного дерева

  void save_to_file_recursive(Node<T> *node, std::ofstream &file) {
    if (node == nullptr) {
      return;
    }

    // Рекурсивно сохраняем данные узла в файл
    file << node->get_data() << " ";

    save_to_file_recursive(node->get_left(), file);
    save_to_file_recursive(node->get_right(), file);
  }

  void clear_tree(Node<T> *node) {
    if (node == nullptr) {
      return;
    }

    clear_tree(node->get_left());
    clear_tree(node->get_right());

    delete node;
  }

public:
  // Получение указателя на корень
  Node<T> *get_head() { return this->_HEAD; }

  // Получение константного указателя на корень
  const Node<T> *get_const_head() const { return this->_HEAD; }

  // Метод добавления элемента в дерево
  bool add_element(T _VALUE) {
    // Создание нового узла с переданным значением
    Node<T> *_TMP = new Node<T>(_VALUE);

    if (!_TMP)
      return false;

    // Получаем указатель на текущий узел (начинаем с корня)
    Node<T> *_CUR = this->get_head();

    // Если дерево пустое, то устанавливаем новый узел как корень
    if (!_CUR) {
      this->_HEAD = _TMP;
      return true;
    }

    // Пока текущий узел существует (проходим по дереву), определяем куда
    // добавить новый узел
    while (_CUR) {
      // Если значение нового узла больше или равно значению текущего узла
      if (_TMP->get_data() >= _CUR->get_data()) {

        // Если у текущего узла нет правого потомка, добавляем новый узел справа
        if (!_CUR->get_right()) {
          _TMP->set_up(_CUR);
          _CUR->set_right(_TMP);
          return true;
        } else
          _CUR = _CUR->get_right(); // Иначе двигаемся вправо по дереву

        // Если значение нового узла меньше значения текущего узла
      } else {

        // Если у текущего узла нет левого потомка, добавляем новый узел слева
        if (!_CUR->get_left()) {
          _TMP->set_up(_CUR);
          _CUR->set_left(_TMP);
          return true;
        } else
          _CUR = _CUR->get_left(); // Иначе двигаемся влево по дереву
      }
    }
    return false; // Возвращаем false, если что-то пошло не так
  }

  // Метод поиска элемента
  bool find_element(Node<T> *_NODE, T &_VALUE) {
    if (_NODE == nullptr)
      return false;

    else if (_VALUE == _NODE->get_data())
      return true;

    else if (_VALUE > _NODE->get_data())
      return find_element(_NODE->get_right(), _VALUE);

    else
      return find_element(_NODE->get_left(), _VALUE);

    return false;
  }

  // Обертка для вызова метода поиска элемента
  bool find_element(T _VALUE) { return find_element(this->get_head(), _VALUE); }

  bool delete_element(Node<T> *current, T value) {
    // Проверка: если текущий узел равен nullptr, то узел не найден
    if (current == nullptr) {
      return false; // Узел не найден
    }

    if (value < current->get_data()) {
      // Рекурсивный вызов для левого поддерева, если значение для удаления
      // меньше значения текущего узла
      return delete_element(current->get_left(), value);
    } else if (value > current->get_data()) {
      // Рекурсивный вызов для правого поддерева, если значение для удаления
      // больше значения текущего узла
      return delete_element(current->get_right(), value);
    } else {
      // Узел с данным значением найден, начинаем процесс удаления
      if (!current->get_left()) {
        // Если у узла нет левого потомка
        Node<T> *temp = current->get_right();
        // Замена узла на его правого потомка
        transplant(current, current->get_right());
        // Удаление текущего узла
        delete current;
        return true;
      } else if (!current->get_right()) {
        // Если у узла нет правого потомка
        Node<T> *temp = current->get_left();
        // Замена узла на его левого потомка
        transplant(current, current->get_left());

        // Удаление текущего узла
        delete current;
        return true;
      } else {
        // Если у узла есть оба потомка
        // Находим минимальное значение в правом поддереве
        Node<T> *min_right = find_min(current->get_right());

        // Замена значения текущего узла на
        // минимальное значение из правого поддерева
        current->set_data(min_right->get_data());

        // Рекурсивный вызов для удаления узла с
        // минимальным значением из правого поддерева
        return delete_element(current->get_right(), min_right->get_data());
      }
    }

    return false; // Неожиданный результат
  }

  Node<T> *find_min(Node<T> *current) {
    // Нахождение минимального узла (поиск крайнего левого узла)
    while (current->get_left()) {
      current = current->get_left();
    }
    return current;
  }

  void transplant(Node<T> *u, Node<T> *v) {
    // Замена узла u на узел v
    if (u->get_up() == nullptr) {
      // Если узел u является корневым, заменяем корневой узел на v
      this->_HEAD = v;
    } else if (u == u->get_up()->get_left()) {
      // Если u является левым потомком своего родителя, заменяем его родителю
      // левого потомка на v
      u->get_up()->set_left(v);
    } else {
      // Иначе, заменяем правого потомка родителя узла u на v
      u->get_up()->set_right(v);
    }
    if (v != nullptr) {
      // Устанавливаем указатель на родителя для узла v
      v->set_up(u->get_up());
    }
  }

  // Обертка для вызова метода удаления элемента
  bool delete_element(T _VALUE) {
    return delete_element(this->get_head(), _VALUE);
  }

  // Метод для вывода дерева в терминал
  void print_tree(Node<T> *_NODE, int _DEPTH = 0) {
    if (_NODE == nullptr)
      return;

    // Рекурсивный вызов для правого потомка
    print_tree(_NODE->get_right(), _DEPTH + 1);

    // Вывод узла с добавлением пробелов для отображения уровня в дереве
    for (int i = 0; i < _DEPTH; i++) {
      std::cout << "      ";
    }

    std::cout << _NODE->get_data() << std::endl;

    // Рекурсивный вызов для левого потомка
    print_tree(_NODE->get_left(), _DEPTH + 1);
  }

  // Обертка для вызова метода с корневого узла
  void print_tree() { print_tree(this->get_head()); }

  bool save_to_file(const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file for writing." << std::endl;
            return false;
        }

        save_to_file_recursive(this->get_head(), file);

        file.close();
        return true;
    }

    bool load_from_file(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
            return false;
        }

        // Очищаем существующее дерево перед загрузкой новых данных
        clear_tree(this->get_head());

        T value;
        while (file >> value) {
            add_element(value);
        }

        file.close();
        return true;
    }
};

#endif
