#ifndef BINTREE_HPP_
#define BINTREE_HPP_

#include "binode.hpp"
#include <fstream>
#include <iostream>

template <class T> class BSTree {
private:
  Node<T> *_HEAD; // Узел-корень бинарного дерева

  // Метод замены (переноса) узлов
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

public:
  // Получение указателя на корень
  Node<T> *get_head() { return this->_HEAD; }

  // Получение константного указателя на корень
  const Node<T> *get_const_head() const { return this->_HEAD; }

  // Конструктор по умолчанию
  BSTree() { this->_HEAD; }

  // Конструктор с инициализацией данных
  BSTree(T _DATA) { this->_HEAD(_DATA); }

  // Деструктор
  ~BSTree() { clear_tree(this->_HEAD); };

  // Метод реурсивного удаления дерева
  void clear_tree(Node<T> *_NODE) {
    if (_NODE == nullptr)
      return;

    clear_tree(_NODE->get_left());
    clear_tree(_NODE->get_right());

    delete _NODE;
  }

  // Метод добавления элемента в дерево
  bool add_element(T _VALUE) {
    // Создание нового узла с переданным значением
    Node<T> *_TMP = new Node<T>(_VALUE);
    // Проверка существоваия ноды
    if (!_TMP)
      return false;

    // Получаем указатель на текущий узел (начинаем с корня)
    Node<T> *_CUR = this->get_head();
    // Если дерево пустое, то устанавливаем новый узел как корень
    if (!_CUR || !_CUR->get_data()) {
      this->_HEAD = _TMP;
      return true;
    }

    // Пока текущий узел существует (проходим по дереву), определяем куда
    // добавить новый узел
    while (_CUR) {
      if (_VALUE == _CUR->get_data()) return false;
      // Если значение нового узла больше значения текущего узла
      if (_TMP->get_data() > _CUR->get_data()) {

        // Если у текущего узла нет правого потомка, добавляем новый узел справа
        if (!_CUR->get_right()) {
          _TMP->set_up(_CUR);
          _CUR->set_right(_TMP);
          return true;

        } else
          // Иначе двигаемся вправо по дереву
          _CUR = _CUR->get_right();

        // Если значение нового узла меньше значения текущего узла
      } else {
        // Если у текущего узла нет левого потомка, добавляем новый узел слева
        if (!_CUR->get_left()) {
          _TMP->set_up(_CUR);
          _CUR->set_left(_TMP);
          return true;

        } else
          // Иначе двигаемся влево по деревуs
          _CUR = _CUR->get_left();
      }
    }
    // Возвращаем false, если что-то пошло не так
    return false;
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
  bool find_element(T _VALUE) {
    return find_element(this->get_head(), _VALUE);
  }

  // Метод удаления элемента
  bool delete_element(Node<T> *_CUR, T _VALUE) {
    // Проверка: если текущий узел равен nullptr, то узел не найден
    if (_CUR == nullptr)
      // Узел не найден
      return false;

    if (_VALUE < _CUR->get_data())
      // Рекурсивный вызов для левого поддерева, если значение для удаления
      // меньше значения текущего узла
      return delete_element(_CUR->get_left(), _VALUE);

    else if (_VALUE > _CUR->get_data())
      // Рекурсивный вызов для правого поддерева, если значение для удаления
      // больше значения текущего узла
      return delete_element(_CUR->get_right(), _VALUE);
    else {
      // Узел с данным значением найден, начинаем процесс удаления
      if (!_CUR->get_left()) {
        // Если у узла нет левого потомка
        Node<T> *temp = _CUR->get_right();

        // Замена узла на его правого потомка
        transplant(_CUR, _CUR->get_right());

        // Удаление текущего узла
        delete _CUR;
        return true;

      } else if (!_CUR->get_right()) {
        // Если у узла нет правого потомка
        Node<T> *temp = _CUR->get_left();

        // Замена узла на его левого потомка
        transplant(_CUR, _CUR->get_left());

        // Удаление текущего узла
        delete _CUR;
        return true;

      } else {
        // Если у узла есть оба потомка
        // Находим минимальное значение в правом поддереве
        Node<T> *min_right = find_min(_CUR->get_right());

        // Замена значения текущего узла на
        // минимальное значение из правого поддерева
        _CUR->set_data(min_right->get_data());

        // Рекурсивный вызов для удаления узла с
        // минимальным значением из правого поддерева
        return delete_element(_CUR->get_right(), min_right->get_data());
      }
    }

    return false; // Неожиданный результат
  }

  // Обертка для вызова метода удаления элемента
  bool delete_element(T _VALUE) {
    return delete_element(this->get_head(), _VALUE);
  }

  // Метод поиска наименьшего элемента
  Node<T> *find_min(Node<T> *_CUR) {
    // Нахождение минимального узла (поиск крайнего левого узла)
    while (_CUR->get_left()) {
      _CUR = _CUR->get_left();
    }
    return _CUR;
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

   // Метод записи в файл
  bool save_to_file(Node<T> *node, std::ofstream &_FILE) {
    if (node == nullptr)
      return true;

    // Рекурсивно сохраняем данные узла в файл
    _FILE << node->get_data() << " ";

    save_to_file(node->get_left(), _FILE);
    save_to_file(node->get_right(), _FILE);
    return true;
  }

  // Обертка для вызова метода записи в файл
  bool save_to_file(const std::string &_PATH) {
    std::ofstream _FILE(_PATH);
    if (!_FILE.is_open()) {
      std::cerr << "[-] Error: Unable to open file for writing." << std::endl;
      return false;
    }

    save_to_file(this->get_head(), _FILE);

    _FILE.close();
    return true;
  }

  // Метод чтения из файла
  bool load_from_file(const std::string &_PATH) {
    std::ifstream _FILE(_PATH);
    if (!_FILE.is_open()) {
      std::cerr << "[-] Error: Unable to open file for reading." << std::endl;
      return false;
    }

    // Очищаем существующее дерево перед загрузкой новых данных
    clear_tree(this->get_head());

    T value;
    while (_FILE >> value) {
      add_element(value);
    }

    _FILE.close();
    return true;
  }
};

#endif
