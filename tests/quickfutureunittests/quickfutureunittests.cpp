#include <QQmlApplicationEngine>
#include <QTest>
#include <Automator>
#include <QQmlContext>
#include <QtShell>
#include <QFFuture>
#include "actor.h"
#include "quickfutureunittests.h"

Q_DECLARE_METATYPE(QFuture<QString>)

QuickFutureUnitTests::QuickFutureUnitTests(QObject *parent) : QObject(parent)
{

}

void QuickFutureUnitTests::test_QFVariantWrapper()
{
    QFuture<QString> future;
    QVariant v = QVariant::fromValue<QFuture<QString> >(future);

    QVERIFY(future.isFinished());

    QFVariantWrapper<QString> wrapper;
    QVERIFY(wrapper.isFinished(v));


}

void QuickFutureUnitTests::test_QFFuture()
{
    QFFuture wrapper;
    QFuture<QString> future;
    QVariant v = QVariant::fromValue<QFuture<QString> >(future);

    QVERIFY(future.isFinished());
    QVERIFY(wrapper.isFinished(v));
}

void QuickFutureUnitTests::PromiseIsNotInstalled()
{
    QQmlApplicationEngine engine;

    qDebug() << "Excepted error:";

    engine.rootContext()->setContextProperty("Actor", new Actor());

    engine.load(QString(SRCDIR) + "/qmltests/PromiseIsNotInstalled.qml");

    QObject* object = engine.rootObjects().first();
    QVERIFY(object);

    QMetaObject::invokeMethod(object, "test",Qt::DirectConnection);

}
