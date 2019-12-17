#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include"QFileDialog"
#include"QString"
#include"QObject"
class fileOperation
{
private:
    QFileDialog* fd;

public:
    fileOperation(){fd = nullptr;}
    ~fileOperation(){delete fd;fd = nullptr;}

    void openFile()
    {
        fd = new QFileDialog();
        QString fileName = fd->getOpenFileName(QObject::tr("Open File"),"/home",QObject::tr("Excel(*.csv)"));
    }

    void readFile()
    {

    }
};

#endif // FILEOPERATION_H
