#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();

    QMap<QString, QAction*> actionMap;

    GLWidget *glwidget;
    QVBoxLayout *verticalLayout;
    QToolBar *toolBar;

private:
    Q_SLOT void openFile();
};

#endif // MAINWINDOW_H
