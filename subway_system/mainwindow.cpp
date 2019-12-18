#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"iostream"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set the displayformat style
    ui->startTime->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->endTime->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    //fileOperation
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    //openAction->setShortcuts(QKeySequence::Open);

    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    //quitAction->setShortcuts(QKeySequence::Quit);

    QAction *chooseAction = fileMenu->addAction(tr("&Choose a folder..."));


    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(chooseAction,&QAction::triggered,this,&MainWindow::chooseFolder);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    menuBar()->addMenu(fileMenu);
    statusBar();



    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);

    QStringList header;
    header<<tr("time")<<tr("lineID")<<tr("stationID")<<tr("deviceID")<<tr("status")
         <<tr("userID")<<tr("payType");
    ui->tableWidget->setHorizontalHeaderLabels(header);


    int Flag = 0;
    if(QString::compare(QString("1 2"),QString("1 0")) > 0)
        qDebug(">");
    if(QString::compare(QString("1 1"),QString("1 2")) < 0)
        qDebug("<");
    if(QString::compare(QString("1 1"),QString("1 1")) == 0)
        qDebug("=");


    setWindowTitle(tr("Metro"));
    resize(1000, 600);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFile()
{
    const QString fileName =
        QFileDialog::getOpenFileName(this, tr("Choose a data file"), "", "*.csv");
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::chooseFolder()
{
    //qDebug("choose folder\n");
    const QString srcDirPath = QFileDialog::getExistingDirectory(
                this, "choose src Directory",
                 "/");
    QDir dir(srcDirPath);

    QStringList nameFilters;
    nameFilters << "*.csv";
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(nameFilters);


    //qDebug("%s",qPrintable(srcDirPath));

    //qDebug("%d\n",dir.count());

    QStringList string_list;
    for(int i=0; i < dir.count(); i++)
    {
        QString file_name = srcDirPath + "/";  //文件名称
        file_name.append(dir[i]);
        string_list.append(file_name);
    }

    loadFiles(string_list);
    //qDebug("choose folder complete...\n");
}
void MainWindow::loadFile(const QString &fileName)
{
    ui->tableWidget->setColumnHidden(0, !ui->checkBox->isChecked());
    ui->tableWidget->setColumnHidden(1, !ui->checkBox_2->isChecked());
    ui->tableWidget->setColumnHidden(2, !ui->checkBox_3->isChecked());
    ui->tableWidget->setColumnHidden(3, !ui->checkBox_4->isChecked());
    ui->tableWidget->setColumnHidden(4, !ui->checkBox_5->isChecked());
    ui->tableWidget->setColumnHidden(5, !ui->checkBox_6->isChecked());
    ui->tableWidget->setColumnHidden(6, !ui->checkBox_7->isChecked());

    //qDebug("file name is %s\n",qPrintable(fileName));
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;

    QTextStream stream(&file);

    //ui->tableWidget->clearContents();

    bool flag = true;
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            const QStringList pieces = line.split(',', QString::SkipEmptyParts);
            if (flag)
            {
                flag = false;
                continue;
            }
            time.append(pieces.value(0));
            lineID.append(pieces.value(1));
            stationID.append(pieces.value(2).toInt());
            stationID_str.append(pieces.value(2));
            deviceID.append(pieces.value(3).toInt());
            deviceID_str.append(pieces.value(3));
            status.append(pieces.value(4).toInt());
            status_str.append(pieces.value(4));
            userID.append(pieces.value(5));
            payType.append(pieces.value(6).toInt());
            payType_str.append(pieces.value(6));
        }
    }

    file.close();
    statusBar()->showMessage(tr("Loaded %1").arg(fileName), 2000);
    tableShow();
}

void MainWindow::loadFiles(const QStringList &stringlist)
{
    ui->tableWidget->setColumnHidden(0, !ui->checkBox->isChecked());
    ui->tableWidget->setColumnHidden(1, !ui->checkBox_2->isChecked());
    ui->tableWidget->setColumnHidden(2, !ui->checkBox_3->isChecked());
    ui->tableWidget->setColumnHidden(3, !ui->checkBox_4->isChecked());
    ui->tableWidget->setColumnHidden(4, !ui->checkBox_5->isChecked());
    ui->tableWidget->setColumnHidden(5, !ui->checkBox_6->isChecked());
    ui->tableWidget->setColumnHidden(6, !ui->checkBox_7->isChecked());

    //qDebug("load files with %d\n",stringlist.count());

    QString fileName;

    int i = 0;
    while(i < stringlist.count())
    {
        fileName = stringlist[i];

        i++;
        if(i > 5)
            break;

        //qDebug("file name is %s\n",qPrintable(fileName));
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text))
            continue;

        QTextStream stream(&file);
        bool flag = true;

        while (!stream.atEnd()) {
            const QString line = stream.readLine();
            if (!line.isEmpty()) {
                const QStringList pieces = line.split(',', QString::SkipEmptyParts);
                if (flag)
                {
                    flag = false;
                    continue;
                }
                time.append(pieces.value(0));
                lineID.append(pieces.value(1));
                stationID.append(pieces.value(2).toInt());
                stationID_str.append(pieces.value(2));
                deviceID.append(pieces.value(3).toInt());
                deviceID_str.append(pieces.value(3));
                status.append(pieces.value(4).toInt());
                status_str.append(pieces.value(4));
                userID.append(pieces.value(5));
                payType.append(pieces.value(6).toInt());
                payType_str.append(pieces.value(6));
            }
        }


        file.close();
        tableShow();
        statusBar()->showMessage(tr("Loaded %1").arg(fileName), 2000);
    }
}
void MainWindow::tableShow()
{
    int row = ui->tableWidget->rowCount();
    QVector<QString>::iterator iter_1,iter_2,iter_6;
    QVector<QString>::iterator iter_3,iter_4,iter_5,iter_7;
    iter_1 = time.begin() + row;
    iter_2 = lineID.begin() + row;
    iter_3 = stationID_str.begin() + row;
    iter_4 = deviceID_str.begin() + row;
    iter_5 = status_str.begin() + row;
    iter_6 = userID.begin() + row;
    iter_7 = payType_str.begin() + row;



    while(iter_1 != time.end())
    {
        if(row == 1)
        {
            ui->tableWidget->resizeRowsToContents();
            ui->tableWidget->resizeColumnsToContents();
        }

        ui->tableWidget->insertRow(row); //插入新行

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(*iter_1));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(*iter_2));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(*iter_3));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(*iter_4));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(*iter_5));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(*iter_6));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(*iter_7));

        row++;
        iter_1++;
        iter_2++;
        iter_3++;
        iter_4++;
        iter_5++;
        iter_6++;
        iter_7++;
    }


}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(0, !ui->checkBox->isChecked());
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(1, !ui->checkBox_2->isChecked());
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(2, !ui->checkBox_3->isChecked());
}


void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(3, !ui->checkBox_4->isChecked());
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(4, !ui->checkBox_5->isChecked());
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(5, !ui->checkBox_6->isChecked());
}

void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    ui->tableWidget->setColumnHidden(6, !ui->checkBox_7->isChecked());
}

void MainWindow::on_set_filter_clicked()
{

    qDebug("set_filter_clicked\n");

    int RC = ui->tableWidget->rowCount();


    qDebug("table row is %d",RC);

    for(int i = 0;i < RC;i++)
    {
        ui->tableWidget->setRowHidden(i,true);
    }
    qDebug("All rows have been hidden\n");

    int* point = new int[RC];
    bool flag[7];
    flag[0] = ui->lineA->isChecked();
    flag[1] = ui->lineB->isChecked();
    flag[2] = ui->lineC->isChecked();
    flag[3] = ui->type_1->isChecked();
    flag[4] = ui->type_2->isChecked();
    flag[5] = ui->type_3->isChecked();
    flag[6] = ui->type_4->isChecked();

    int symbol = (flag[0] || flag[1] || flag[2]) + (flag[3] || flag[4] ||flag[5] || flag[6]) + 1;

    //line filter


    if(flag[0])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("A",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==1)
                    point[item.at(i)->row()]++;
            }
        }
    }
    if(flag[1])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("B",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==1)
                    point[item.at(i)->row()]++;
            }
        }
    }
    if(flag[2])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("C",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==1)
                    point[item.at(i)->row()]++;
            }
        }
    }

    //pay type filter

    if(flag[3])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("0",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==6)
                    point[item.at(i)->row()]++;
            }
        }
    }
    if(flag[4])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("1",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==6)
                    point[item.at(i)->row()]++;
            }
        }
    }
    if(flag[5])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("2",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==6)
                    point[item.at(i)->row()]++;
            }
        }
    }
    if(flag[6])
    {
        QList<QTableWidgetItem*> item = ui->tableWidget->findItems("3",Qt::MatchContains);
        if(!item.isEmpty())
        {
            for(int i = 0;i < item.count();i++)
            {
                if(item.at(i)->column()==6)
                    point[item.at(i)->row()]++;
            }
        }
    }


    QString date1 = ui->startTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString date2 = ui->endTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");



    //qDebug("%s",qPrintable(date1));
    //qDebug("%s",qPrintable(date2));

    for(int i = 0;i < RC;i++)
    {
        if((!(QString::compare(time[i],date1) < 0 ))&&(!(QString::compare(time[i],date2) > 0 )))
        {
            point[i]++;
        }
    }


    for(int i = 0;i < RC;i++)
    {
        if(point[i] == symbol)
            ui->tableWidget->setRowHidden(i,false);
    }
}

void MainWindow::timeFilter()
{



}
