#ifndef SONGSELECTOR_H
#define SONGSELECTOR_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFileSystemModel>
#include <QStringListModel>
class MSong;

class SongSelector: public QObject
{
    Q_OBJECT
public:
    SongSelector(QObject* parent=0);

    QFileSystemModel* getFSM();
    QStringList getSSM();
    QString getPath();
public slots:
    void selectTreeView(QModelIndex i);
    void selectStringList(int index);
signals:
    void msongSelect(MSong* msong);
    void SelectOk(int index);
private:
    QFileSystemModel* fileSystemModel;
    QStringListModel* stringListModel;
    QStringList sl;
    QDir songDir;
};

#endif // SONGSELECTOR_H
