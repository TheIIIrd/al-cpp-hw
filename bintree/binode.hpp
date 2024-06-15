#ifndef BINODE_HPP_
#define BINODE_HPP_

// Объявляем шаблонный класс Node
template <class T> class Node {

private:
  T _DATA;      // Данные узла
  Node *_UP;    // Указатель на верхний узел
  Node *_LEFT;  // Указатель на левый узел
  Node *_RIGHT; // Указатель на правый узел

public:
  // Методы для установки левого, правого и верхнего узла
  void set_left(Node *_LEFT) { this->_LEFT = _LEFT; }
  void set_right(Node *_RIGHT) { this->_RIGHT = _RIGHT; }
  void set_up(Node *_UP) { this->_UP = _UP; }

  // Методы для получения левого, правого и верхнего узла
  Node *get_left() { return this->_LEFT; }
  Node *get_right() { return this->_RIGHT; }
  Node *get_up() { return this->_UP; }

  // Константные методы для получения левого, правого и верхнего узла
  const Node *get_const_left() const { return this->_LEFT; }
  const Node *get_const_right() const { return this->_RIGHT; }
  const Node *get_const_up() const { return this->_UP; }

  // Метод для установки данных узла
  void set_data(T _DATA) { this->_DATA = _DATA; }

  // Метод для получения данных узла
  T get_data() { return this->_DATA; }

  // Константный метод для получения данных узла
  const T get_const_data() const { return this->_DATA; }

  // Декларация дружественных функций
  friend bool operator<(Node<T> &_LEFTNODE, Node<T> &_RIGHTNODE) {
    if (_LEFTNODE.get_data() < _RIGHTNODE.get_data())
      return true;
    else
      return false;
  }

  friend bool operator>(Node<T> &_LEFTNODE, Node<T> &_RIGHTNODE) {
    if (_LEFTNODE.get_data() > _RIGHTNODE.get_data())
      return true;
    else
      return false;
  }

  friend bool operator==(Node<T> &_LEFTNODE, Node<T> &_RIGHTNODE) {
    if (_LEFTNODE.get_data() == _RIGHTNODE.get_data() &&
        _LEFTNODE.get_up() == _RIGHTNODE.get_up() &&
        _LEFTNODE.get_left() == _RIGHTNODE.get_left() &&
        _LEFTNODE.get_right() == _LEFTNODE.get_right())
      return true;
    else
      return false;
  }

  // Конструктор по умолчанию
  Node() {
    this->_LEFT = nullptr;
    this->_RIGHT = nullptr;
    this->_UP = nullptr;
    this->_DATA = 0.;
  }

  // Конструктор с инициализацией данных
  Node(T _DATA) {
    this->_LEFT = nullptr;
    this->_RIGHT = nullptr;
    this->_UP = nullptr;
    this->_DATA = _DATA;
  }

  // Деструктор
  ~Node(){};
};

#endif
