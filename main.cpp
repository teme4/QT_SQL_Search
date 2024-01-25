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



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");

      QString path = "C:\\SVN\\Altium_Libs_SVN\\DatabaseSVN.accdb";

    m_db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access}; DBQ="+path); //путь к БД

    bool  ok = m_db.open();
    if(ok)
        qDebug()<<"База открыта";
    else
        qDebug()<<"Не удалось открыть базу";

    QSqlQuery query;

QString value="5CGXBC4C7U19C";
QString comment,OrderCode,PartNumber;


   QStringList list = m_db.tables(QSql::Tables);
   //qDebug() <<"Views list\n " <<list.join(",").toLocal8Bit().data()<<"\n";


qint16 flag=0;
    for(int i=0;i<list.count()-3;i++)//list.count()- 3
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
        // if(flag==0)
            //  qDebug() << "В таблице-> "+list[i]+" не найдено";


}
    return 0;
}
