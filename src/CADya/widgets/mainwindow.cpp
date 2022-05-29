#include "widgets/mainwindow.hpp"

#include "widgets/glcanvas.hpp"

#include <QAction>

MainWindow::MainWindow(QWidget * parent)
  : QMainWindow(parent)
{
    createActions();

    setCentralWidget(new GLCanvas{this});
}

void MainWindow::createActions()
{
    auto quitAction = new QAction{this};
    quitAction->setShortcut(QKeySequence{Qt::CTRL + Qt::Key_Q});
    connect(quitAction, &QAction::triggered,
        this, &QWidget::close
    );
    addAction(quitAction);
}
