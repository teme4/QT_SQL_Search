#include <QApplication>
#include <QCoreApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
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



void MainWindow::on_pushButton_clicked()
{
   /* QSqlQuery query;
    QString comment,OrderCode,PartNumber;
    QString path,value;
    bool  ok,flag,flag2 ;*/

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");
    ui->textEdit_3->setText(NULL);
    QString value;//="5CGXBC4C7U19C";
     //value=ui->textEdit_2->toMarkdown();
    QString comment,OrderCode,PartNumber;
    QString path;
        path=ui->lineEdit_2->text();
        value=ui->lineEdit_1->text();
       m_db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access}; DBQ="+path); //путь к БД

       bool  ok = m_db.open();
       if(ok)
           qDebug()<<"База открыта";
       else
           qDebug()<<"Не удалось открыть базу!";

       QSqlQuery query;
       QStringList list = m_db.tables(QSql::Tables);
      //qDebug() <<"Views list\n " <<list.join(",").toLocal8Bit().data()<<"\n";


   qint16 flag=0;
       for(int i=0;i<list.count()-3;i++)//list.count()-3
       {
             // flag=0;
              query.exec("SELECT * FROM "+list[i]+" WHERE PartNumber LIKE '"+value+"%'");
              if (!query.isActive())
                  {
                      //QMessageBox::warning(0, "Database Error", query.lastError().text());
                  }
              QSqlRecord rec = query.record();
              while (query.next())
              {
                  flag=1;
                      comment = query.value(rec.indexOf("comment")).toString();
                      OrderCode = query.value(rec.indexOf("OrderCode")).toString();
                      PartNumber = query.value(rec.indexOf("PartNumber")).toString();

                      ui->textEdit_3->setText("Найдено в таблице-> " + list[i] +"\r\n"+ "PartNumber-> " +PartNumber);
                    //  qDebug() << "Найдено в таблице-> " << list[i];
                    // qDebug() << "PartNumber-> " <<PartNumber;
              }

}
       if(flag==0)
          ui->textEdit_3->setText("Не найдено");
          //  qDebug() << "В таблице-> "+list[i]+" не найдено";

}
