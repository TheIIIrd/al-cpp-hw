#ifndef BINSTREE_HPP_
#define BINSTREE_HPP_

#include "binode.hpp"
#include <iostream>

template <class T> class BSTree {
private:
  Node<T> *_HEAD; // Узел-корень бинарного дерева

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

  // Метод удаления элемента
  bool delete_element(Node<T> *_NODE, T &_VALUE) {
    if (_NODE == nullptr)
      return false;

    // Проверка на соответствие значению для удаления
    else if (_VALUE == _NODE->get_data()) {
      // Узел не имеет потомков
      if (!_NODE->get_left() && !_NODE->get_right()) {
        if (_NODE->get_up()->get_left() == _NODE)
          _NODE->get_up()->set_left(nullptr);
        else
          _NODE->get_up()->set_right(nullptr);
        delete _NODE;
        return true;
      }

      // Узел имеет только правого потомка
      else if (!_NODE->get_left()) {
        if (_NODE->get_up()->get_left() == _NODE) {
          _NODE->get_right()->set_up(_NODE->get_up());
          _NODE->get_up()->set_left(_NODE->get_right());
        } else {
          _NODE->get_right()->set_up(_NODE->get_up());
          _NODE->get_up()->set_right(_NODE->get_right());
        }
        delete _NODE;
        return true;
      }

      // Узел имеет только левого потомка
      else if (!_NODE->get_right()) {
        if (_NODE->get_up()->get_left() == _NODE) {
          _NODE->get_left()->set_up(_NODE->get_up());
          _NODE->get_up()->set_left(_NODE->get_left());
        } else {
          _NODE->get_left()->set_up(_NODE->get_up());
          _NODE->get_up()->set_right(_NODE->get_left());
        }
        delete _NODE;
        return true;
      }

      // Узел имеет обоих потомков
      else {
        Node<T> *_TEMP = _NODE->get_right();

        // Находим левое свободное место в правом поддереве
        while (_TEMP->get_left()) {
          _TEMP = _TEMP->get_left();
        }

        // Переносим связи узлов
        if (_NODE->get_up()->get_left() == _NODE) {
          _NODE->get_right()->set_up(_NODE->get_up());
          _NODE->get_up()->set_left(_NODE->get_right());
        } else {
          _NODE->get_right()->set_up(_NODE->get_up());
          _NODE->get_up()->set_right(_NODE->get_right());
        }

        _NODE->get_left()->set_up(_TEMP->get_up());
        _TEMP->set_left(_NODE->get_left());

        delete _NODE;
        return true;
      }

      return true;
    }

    // Рекурсивный вызов метода для правого поддерева
    else if (_VALUE >= _NODE->get_data())
      return delete_element(_NODE->get_right(), _VALUE);

    // Рекурсивный вызов метода для левого поддерева
    else
      return delete_element(_NODE->get_left(), _VALUE);

    return false;
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
};

#endif