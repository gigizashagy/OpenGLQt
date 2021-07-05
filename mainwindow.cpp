#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QLabel>
#include "fileloader.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMenuBar(new QMenuBar(this));
    setStatusBar(new QStatusBar(this));
    QMenu *menuFile = new QMenu(tr("File"));
    menuBar()->addMenu(menuFile);

    glwidget = new GLWidget(this);

    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    toolBar->setAcceptDrops(false);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    toolBar->addAction(new QAction("PUPA"));
    addToolBar(Qt::TopToolBarArea, toolBar);
    setCentralWidget(glwidget);

    createActions();

    menuFile->addAction(actionMap["AOpenFile"]);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    actionMap.insert("AOpenFile", new QAction(tr("Open"), this));
    connect(actionMap["AOpenFile"], &QAction::triggered, this, &MainWindow::openFile);
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Open file"), "",
                                                    tr("obj (*.obj);;All Files (*)"));
    if (filename.isEmpty()) return;
    qDebug() << filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(nullptr, tr("Unable to open file"),
                                 file.errorString());

    }

    QDataStream stream(&file);
    QByteArray buffer;
    char *raw;
    uint len = 64;
    while (stream.status() != QDataStream::ReadPastEnd)
    {
         stream.readRawData(raw, len);
    qDebug() << raw;

    }

    file.close();

}
