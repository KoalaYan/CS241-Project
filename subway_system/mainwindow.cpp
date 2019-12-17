#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"iostream"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //fileOperation
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    QAction *openAction = fileMenu->addAction(tr("&Open..."));
    openAction->setShortcuts(QKeySequence::Open);

    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    quitAction->setShortcuts(QKeySequence::Quit);

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    menuBar()->addMenu(fileMenu);
    statusBar();

    std::cout<<"test1\n";

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);

    //ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    //ui->tableWidget->horizontalHeader()->setClickable(false);
    QStringList header;
    header<<tr("time")<<tr("lineID")<<tr("stationID")<<tr("deviceID")<<tr("status")
         <<tr("userID")<<tr("payType");
    ui->tableWidget->setHorizontalHeaderLabels(header);


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

void MainWindow::loadFile(const QString &fileName)
{
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

void MainWindow::tableShow()
{
    QVector<QString>::iterator iter_1,iter_2,iter_6;
    QVector<QString>::iterator iter_3,iter_4,iter_5,iter_7;
    iter_1 = time.begin();
    iter_2 = lineID.begin();
    iter_3 = stationID_str.begin();
    iter_4 = deviceID_str.begin();
    iter_5 = status_str.begin();
    iter_6 = userID.begin();
    iter_7 = payType_str.begin();

    int row = ui->tableWidget->rowCount();
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

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{

}
