#include <Python.h>

namespace python {

namespace gil {

struct release {
  PyThreadState state;
  bool active;

  release() : state(PyEval_SaveThread()), active(true) {}

  ~release() {
    if (active) {
      restore();
    }
  }

  void restore() {
    PyEval_RestoreThread(state);
    active = false;
  }
};

struct ensure {
  PyGILState_STATE state;
  bool active;

  ensure() : state(PyGILState_Ensure()), active(true) {}

  ~ensure() {
    if (active) {
      restore();
    }
  }

  void restore() {
    PyGILState_Release(state);
    active = false;
  }
};
}  // namespace gil
}  // namespace py
