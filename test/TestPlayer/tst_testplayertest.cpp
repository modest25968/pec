#include <QString>
#include <QtTest>
#include <QSettings>

#include "../../src/backLoader/backloader.h"
#include "../../src/core/abstractbackend.h"

#include "../../src/player/player.h"
#include "../../src/parser/parser.h"
#include "../../src/player/msong.h"
class TestPlayer : public QObject
{
    Q_OBJECT

public:
    TestPlayer();

private Q_SLOTS:
    void testLoadAB();
    void testPlayer();
};



TestPlayer::TestPlayer()
{
    QCoreApplication::setOrganizationName("TestOrg");
    QCoreApplication::setApplicationName("Pec");
}

void TestPlayer::testLoadAB()
{
    QSettings settings;
    settings.setValue("back/nameBackEnd", QString("fluidback"));

    BackLoader* bl = new BackLoader();
    AbstractBackend* ab = bl->getBack();
    QVERIFY(ab != nullptr);
    QCOMPARE(ab->textError, QString(""));
    ab->noteOn(1,60);
    QThread::msleep(100000);
    ab->noteOff(1,60);
    delete bl;
}



void TestPlayer::testPlayer()
{

    Player player;
    XmlParser parser;
    MSong* msong = new MSong;

    QDir d(QDir::current());
    d.cd("../../../pe/test/TestPlayer/V1.1");

    parser.parse(d.absoluteFilePath("testPlayer.xml"), nullptr, msong);

    player.setSong(msong);
    player.startPlay();
    //connect(player.timer, SIGNAL(timeout()),SLOT(DebugSlot()));
    qDebug()<<"start ok";
    QThread::msleep(2000);
    player.stopPlay();
    qDebug()<<"stop ok";
}

QTEST_MAIN(TestPlayer)

#include "tst_testplayertest.moc"
