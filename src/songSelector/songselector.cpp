#include "songselector.h"
#include <QDebug>
#include <QMessageBox>
#include <QSettings>

#include "../parser/parser.h"
#include "../player/msong.h"
SongSelector::SongSelector(QObject* parent): QObject(parent)
{
    songDir = QDir::current();
    QSettings settings;
    QString path = settings.value("open/songPath","songs").toString();

    fileSystemModel = new QFileSystemModel(this);
    stringListModel = new QStringListModel(this);

    fileSystemModel->setRootPath(songDir.path());

    //QStringList FiltersName;
    //FiltersName << "*.pe" <<"*.xml";
    /*songDir.setNameFilters(FiltersName);
    QFileInfoList list = songDir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        sl<<list.at(i).fileName();
    }
    stringListModel->setStringList(sl);
*/

    //FiltersName << "*.pe" <<"*.xml";
    //fileSystemModel->setNameFilters(FiltersName);
    //fileSystemModel->setNameFilterDisables(false);

    qDebug()<<"Create list OK "<<songDir.path();

}

QString SongSelector::getPath()
{
    return songDir.path();
}

QFileSystemModel* SongSelector::getFSM()
{
    return fileSystemModel;
}

QStringList SongSelector::getSSM()
{
    return sl;
}

void SongSelector::selectTreeView(QModelIndex i)
{
    qDebug()<<"OPEN";
    QString fileName = fileSystemModel->filePath(i);
    qDebug()<<"file path: "<<fileName;

    if (fileName.endsWith(".xml"))
    {
        XmlParser parser;
        MSong* msong = new MSong();
        parser.parse(fileName, nullptr, msong);
        //setWindowTitle(msong->getName());
        if (parser.ok)
            emit msongSelect(msong);
        else
        {
            //QMessageBox::warning(0, "Ошибка", "Не удалось открыть песню \n"+fileName+"\nОшибка:"+parser.ErrorText);
            delete(msong);
        }
    }
}

void SongSelector::selectStringList(int index)
{
    QString fileName = getPath()+'/'+sl.at(index);

    qDebug()<<"file path: "<<fileName;

    if (fileName.endsWith(".xml"))
    {
        XmlParser parser;
        MSong* msong = new MSong();
        parser.parse(fileName, nullptr, msong);
        //setWindowTitle(msong->getName());
        if (parser.ok)
        {
            emit msongSelect(msong);
            emit SelectOk(index);

        }
        else
        {
            //qDebug()<<"Не удалось открыть песню \n"+fileName+"\nОшибка:"+parser.ErrorText;
//            QMessageBox::warning(0, "Ошибка", "Не удалось открыть песню \n"+fileName+"\nОшибка:"+parser.ErrorText);
            delete(msong);
        }
    }
//        wi->peOpen(fileName);
//    else if (fileName.endsWith(".xml"))
//        wi->xmlOpen(fileName);


//    qDebug()<<"select new index:"<<index<<" path:"<<sl.at(index);
}
