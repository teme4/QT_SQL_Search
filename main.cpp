#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");

      QString path = "C:\\SVN\\Altium_Libs_SVN\\DatabaseSVN.accdb";
      QString tables[]={"3D","ADC","Analog"};

        m_db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access}; DBQ="+path); //путь к БД

    bool  ok = m_db.open();
    if(ok)
        qDebug()<<"База открыта";
    else
        qDebug()<<"Не удалось открыть базу";



    QSqlQuery query;
    // QSqlRecord rec;
QString value="PT2512FK-7W0R28";
  QString comment,OrderCode,PartNumber;


    QStringList list = m_db.tables(QSql::Tables);
  // qDebug() <<"Views list\n " <<list.join(",").toLocal8Bit().data()<<"\n";


qint16 flag=0;
    for(int i=0;i<list.count()-3;i++)//list.count()-3
    {
        flag=0;
        // query.first();
         query.exec("SELECT * FROM "+list[i]+" WHERE PartNumber = '"+value+"'");

        // query.prepare("SELECT * FROM "+list[i]+" WHERE PartNumber = '"+value+"'");
       //  query.exec();
        // query->prepare("select score from Player_info where ID=:y"); // готовим запрос
        // query->bindValue(":y", y);  // присоединяем к запросу данные

      // qDebug()<<("SELECT * FROM "+list[i]+" WHERE PartNumber = 'AD7467BRT'");
       // qDebug() <<"SELECT * FROM ADC WHERE PartNumber = 'AD7467BRT'";

          QSqlRecord rec = query.record();
           while (query.next())
           {
               flag=1;
                   comment = query.value(rec.indexOf("comment")).toString();
                   OrderCode = query.value(rec.indexOf("OrderCode")).toString();
                   PartNumber = query.value(rec.indexOf("PartNumber")).toString();
                   qDebug() << "Найдено в таблице-> " << list[i];
           }
           if(flag==0)
               qDebug() << "В таблице-> "+list[i]+" не найдено";
    }






    return a.exec();
}
