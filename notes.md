# Getting Started Programming with Qt Widgets
- QApplication object manages application-wide resources and it necessary to run any Qt program that uses Qt Widgets.
For GUI applications that do not use Qt Widgets, you can use QGuiApplication instead.
- return a.exec(); makes the QApplication enter its event loop.
Examples of events are mouse presses and key strokes.
- Qt User Interface Compiler(uic)
reads the .ui file and creates a corresponding C++ header file, ui_notepad.h.
- <qt_installation_directory>\bin\qt-cmake -GNinja <source_directory>