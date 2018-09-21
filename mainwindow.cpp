#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(4);
    csvModel->setHorizontalHeaderLabels(QStringList() << "Node" << "Inputs" << "Outputs" << "Group" << "Data Source" );


    ui->tableView->setModel(csvModel);

    QFile file("/home/carlo/Development/C++/Qt/Table/InternetOfEnergy.csv");
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

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}
