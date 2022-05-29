#ifndef CADYA_MAINWINDOW_HPP
#define CADYA_MAINWINDOW_HPP

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = nullptr);

private:
    void createActions();
};

#endif
