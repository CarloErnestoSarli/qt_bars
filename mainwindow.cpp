#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTableView>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(4);
    csvModel->setHorizontalHeaderLabels(QStringList() << "Node" << "Inputs" << "Outputs" << "Group" << "Data Source" );

    ui->tableView->setModel(csvModel);

    ReadCsv();

    SetColumnCount(csvModel->rowCount());
    qDebug() << GetColumnCount();

    ui->tableView->resizeRowsToContents();


    ui->chartView->setRenderHint(QPainter::Antialiasing);
    //ui->chartView->setChart(MakeChart());

}


MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}

void MainWindow::SetColumnCount(int c)
{
    columnCount = c;
}

int MainWindow::GetColumnCount()
{
    return columnCount;
}

void MainWindow::ReadCsv()
{
    QFile file("C:/Users/Carlo Ernesto Sarli/Development/C++/Qt/qt_bars/InternetOfEnergy.csv");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File does not exists";
    }else
    {
        QTextStream in(&file);
        in.readLine();
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QList<QStandardItem *> standardItemsList;
            for(QString item : line.split(","))
            {
               standardItemsList.append(new QStandardItem(item));
            }

            csvModel->insertRow(csvModel->rowCount(), standardItemsList);

        }
        file.close();
    }
}

QChart * MainWindow::MakeChart()
{
    QCategoryAxis *axisX = new QCategoryAxis();
    QBarSet *set0 = new QBarSet("Nodes");
//    QBarSet *set1 = new QBarSet("Inputs");
//    QBarSet *set2 = new QBarSet("Outputs");

    for(int i = 0; i < GetColumnCount(); ++i)
    {
        int j = 0;
        QVariant nodes = csvModel->index(i,j).data();
        QString name = nodes.toString();
        *set0 << name.length();
        if(i==0)
        {
           axisX->append(name, i);
        }else
        {
            axisX->append(name, i+0.5);
        }



//        j++;
//        QVariant inputs = csvModel->index(i,j).data();
//        for(QString item : inputs.toString().split(";"))
//        {
//            *set1 << item.length();

//        }
//        j++;
//        QVariant outputs = csvModel->index(i,j).data();
//        for(QString item : outputs.toString().split(";"))
//        {
//            *set2 << item.length();

//        }


    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
//    series->append(set1);
//    series->append(set2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Bar Test");
    chart->setAxisX(axisX, series);
    axisX->setLabelsAngle(-90);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}

void MainWindow::on_columnCountSelector_valueChanged(int arg1)
{
    SetColumnCount(arg1);
}

void MainWindow::on_columnCountButton_clicked()
{
    qDebug() << GetColumnCount();
    ui->chartView->setChart(MakeChart());

}
