#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTreeWidget>
#include <QTextEdit>
#include <QThread>
#include <iostream>
#include "./src/SearchEngine.h"
#include <QObject>

SearchEngine searchEngine;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString dir;

void MainWindow::on_pushButton_clicked()
{
    std::vector<FindFile> files;
    QString searchStr = ui->textEdit->toPlainText();
    dir =  QFileDialog::getExistingDirectory() + '/';
    QTreeWidgetItem *topLevelItem;
    QTreeWidgetItem *item;

    if(dir.length() < 3)
        return;

    if (searchStr.length() < 1)
    {
        QPalette p = ui->textEdit->palette();
        p.setColor(QPalette::Base, QColor(200, 0, 0));
        ui->textEdit->setPalette(p);
        return;
    }

    ui->treeWidget->clear();
    if(searchEngine.searchbyLine(dir.toLocal8Bit().data(), searchStr.toStdString(), files))
    {
        for(size_t i = 0; i < files.size(); i++)
        {
            char *nameFile = files.at(i).nameFile;
            topLevelItem=new QTreeWidgetItem(ui->treeWidget);
            ui->treeWidget->addTopLevelItem(topLevelItem);

            char *cat = searchEngine.concat(dir.toLocal8Bit().data(), nameFile);
            topLevelItem->setText(0, QString::fromLocal8Bit(cat));
            for(size_t j = 0; j < files.at(i).lineNumbers.size(); j++)
            {
                item=new QTreeWidgetItem(topLevelItem);
                item->setText(0, QString::number(files.at(i).lineNumbers.at(j)));
            }
        }
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    std::string str;
    QString qstr = "";
    QTextEdit* le = ui->textEdit_2;
    if(item->childCount() == 0)
    {
        if(searchEngine.getStringF(item->parent()->text(column).toLocal8Bit().data(), item->text(column).toInt(), str))
        {
            qstr = QString::fromStdString(str);
        }
    }
    else
    {
        for(int i = 0; i < item->childCount(); i++)
        {
            QTreeWidgetItem *pod_item = item->child(i);
            int verification = searchEngine.getStringF(item->text(column).toLocal8Bit().data(), pod_item->text(column).toInt(), str);
            if(verification)
                qstr += pod_item->text(column) + '\n' + QString::fromStdString(str) + '\n';
        }
    }
    le->setText(qstr);
}
