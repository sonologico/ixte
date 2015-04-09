#include "mouse.hpp"
#include "config.hpp"

namespace xts {

mouse::mouse(const ruler &ruler_arg, sf::Font &font)
    : _ruler(ruler_arg), _x(0), _y(0), _t_pos(0), _on(false), _in_line(false),
      _str(), _text() {
  _text.setColor(quasi_black);
  _text.setCharacterSize(12);
  _text.setFont(font);
}

void mouse::update_t() {
  _t_pos = _ruler.get_time_at(_x);
  _str = std::to_string(_t_pos);
  _str.erase(_str.find_last_not_of('0') + 1, std::string::npos);
  _text.setString(_str);
}

void mouse::update_position(double x, double y) {
  _x = x;
  _y = y;
  _in_line = _x >= _ruler.line_begin_x() && _x <= _ruler.line_end_x();
  update_t();
}

void mouse::on(bool x) {
  _on = x;
}

void mouse::draw(sf::RenderTarget &target) {
  if (_on && _in_line) {
    _text.setPosition(_x + 7, _y - 7);
    target.draw(_text);
  }
}

}