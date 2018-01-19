#include "backloader.h"
#include <QLibrary>
#include <QDebug>
#include <QDir>
#include <QSettings>

#include "../core/abstractbackend.h"

// #include <QMessageBox>

BackLoader::BackLoader()
{
    ab = nullptr;

    QString name;
    QSettings settings;
    name = settings.value("back/nameBackEnd","fluidback").toString();

    QLibrary lib(name);
    lib.load();
    if (lib.isLoaded())
    {
        typedef AbstractBackend* (*Fun) ();
        Fun getab = (Fun)(lib.resolve("getab"));
        if (getab)
        {
            qDebug()<<"back load ok:"<<name;
            ab = getab();
            return;
        }
    }
    lib.unload();
    qDebug()<<"back load fail"<<lib.errorString();
}

AbstractBackend *BackLoader::getBack()
{
    return ab;
}
