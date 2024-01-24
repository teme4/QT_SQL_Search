#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

#include <QDebug>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlQuery query;
QString comment,OrderCode,PartNumber;
QString path,value;
 bool  ok ;
 QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");

void MainWindow::on_pushButton_clicked()
{


    QStringList list = m_db.tables(QSql::Tables);


qint16 flag=0;
    for(int i=0;i<list.count()-3;i++)//list.count()-3
    {
        flag=0;
         // qDebug() <<query.exec("SELECT * FROM "+list[i]+" WHERE PartNumber = '"+value+"' LIKE '%ERJ-B1BFR'");
         query.exec("SELECT * FROM "+list[i]+" WHERE PartNumber LIKE '"+value+"%'");
         QSqlRecord rec = query.record();
           while (query.next())
           {
               flag=1;
                   comment = query.value(rec.indexOf("comment")).toString();
                   OrderCode = query.value(rec.indexOf("OrderCode")).toString();
                   PartNumber = query.value(rec.indexOf("PartNumber")).toString();
                   qDebug() << "Найдено в таблице-> " << list[i];
                   qDebug() << "PartNumber-> " <<PartNumber;

           }
           /*if(flag==0)
                      qDebug() << "В таблице-> "+list[i]+" не найдено";*/
}
}

void MainWindow::on_pushButton_2_clicked()
{

    ok=m_db.open();
    if(!ok)
    {
   path=ui->textEdit_1->toMarkdown();
   value=ui->textEdit_2->toMarkdown();
   m_db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access}; DBQ="+path); //путь к БД
    ok = m_db.open();
    if(ok)
        qDebug()<<"База открыта";
    else
        qDebug()<<"Не удалось открыть базу";
 }
}
