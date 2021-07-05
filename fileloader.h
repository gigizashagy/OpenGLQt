#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
class QFile;
class FileLoader : public QObject
{
    Q_OBJECT
public:
    explicit FileLoader(QObject *parent = nullptr);

    QDataStream *openFile();

};

#endif // FILELOADER_H
