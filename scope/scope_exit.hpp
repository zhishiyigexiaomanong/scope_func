#pragma once

#include <functional>

class scope_exit {
private:
  std::function<void(void)> _on_exit;
  bool _on_exit_exec = true;

public:
  explicit scope_exit(std::function<void(void)> &&f)
      : _on_exit(f), _on_exit_exec(true){};

  scope_exit(const scope_exit &) = delete;
  scope_exit &operator=(const scope_exit &) = delete;
  scope_exit &operator=(scope_exit &&) = delete;

  scope_exit(scope_exit &&rhs)
      : _on_exit(std::move(rhs._on_exit)), _on_exit_exec(rhs._on_exit_exec) {
    rhs.release();
  }

  void release(void) { _on_exit_exec = false; }

  ~scope_exit() {
    if (_on_exit_exec && _on_exit) {
      _on_exit();
    }
  }
};