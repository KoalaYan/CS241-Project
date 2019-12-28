#include "processthread.h"

processThread::processThread(QObject *parent)
:QThread(parent)
{

}

processThread::~processThread()
{

}

void processThread::run()
{
    emit processStart(QStringLiteral("start"));
}
