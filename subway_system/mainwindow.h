#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"QFile"
#include"QFileDialog"
#include"QTextStream"
#include"QVector"
#include"string"
#include"QString"
#include"QTableWidget"
#include"QTableView"
#include"QStandardItemModel"
#include"QSplitter"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();

    void on_tableWidget_cellChanged(int row, int column);

private:


    QAbstractItemModel *model = nullptr;

    QVector<QString> time;
    QVector<QString> lineID;
    QVector<int> stationID;
    QVector<QString> stationID_str;
    QVector<int> deviceID;
    QVector<QString> deviceID_str;
    QVector<int> status;
    QVector<QString>status_str;
    QVector<QString> userID;
    QVector<int> payType;
    QVector<QString> payType_str;
    QTableWidget *table;


    void loadFile(const QString &path);
    void tableShow(void);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
