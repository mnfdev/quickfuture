#include <QtConcurrent>
#include <Automator>
#include <QtQml>
#include "actor.h"

Actor::Actor(QObject *parent) : QObject(parent)
{

}

QFuture<QString> Actor::read(const QString &fileName)
{
    return QtConcurrent::run([fileName]() -> QString {

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            return "";
        }

        return file.readAll();
    });
}

QFuture<void> Actor::dummy()
{
    return QtConcurrent::run([]() -> void {
        Automator::wait(100);
        return;
    });
}

QFuture<void> Actor::alreadyFinished()
{
    return QFuture<void>();
}


// First, define the singleton type provider function (callback).
static QObject* provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Actor* actor = new Actor();

    return actor;
}

static void init() {
    qmlRegisterSingletonType<Actor>("FutureTests", 1, 0, "Actor", provider);
}

Q_COREAPP_STARTUP_FUNCTION(init)
