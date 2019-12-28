#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QObject>
#include <QThread>

class processThread : public QThread
{
     Q_OBJECT
public:
    processThread(QObject *parent = nullptr);
    ~processThread();

protected:
    void run();

signals:
    void processStart(const QString &);   //处理开始的信号
    void processEnd(const QString &);     //处理结束的信号
};


#endif // PROCESSTHREAD_H
