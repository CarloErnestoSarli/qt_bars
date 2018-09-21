#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QChart>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int columnCount;
    void SetColumnCount(int i);
    int GetColumnCount();
    void ReadCsv();
    QChart * MakeChart();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_columnCountSelector_valueChanged(int arg1);

    void on_columnCountButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *csvModel;;
};

#endif // MAINWINDOW_H
