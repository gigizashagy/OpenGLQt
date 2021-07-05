#include "fileloader.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

FileLoader::FileLoader(QObject *parent)
    : QObject(parent)
{

}

QDataStream *FileLoader::openFile()
{
    QString filename = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Save Address Book"), "",
                                                    tr("obj (*.obj);;All Files (*)"));
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(nullptr, tr("Unable to open file"),
                                     file.errorString());
              return new QDataStream (&file);
        }

    }
    return 0;
}

