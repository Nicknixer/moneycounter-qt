#include "db.h"

db::db(QObject *parent) : QObject(parent)
{
    connect();
    res = new QSqlQuery();
}

void db::addTransaction(double price, QString desc)
{
    QSqlQuery qs;
    qs.exec("INSERT INTO transactions(price, description, date) VALUES('" + QString::number(price) + "', '" + desc + "', '" + QString::number(QDateTime::currentMSecsSinceEpoch()) + "')");
    sendMsg("Операция добавлена");
}

QSqlQuery *db::result()
{
    res->exec("SELECT * FROM transactions");
    return res;
}
void db::connect()
{
    bool newDB = false;
    if(!QFile::exists("db.sqlite"))
    {
        newDB = true;
    }
    data = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    data->setDatabaseName("db.sqlite");
    data->open();
    sendMsg("Подключение к БД установлено");
    if(newDB)
    {
        QSqlQuery qs;
        qs.exec("CREATE TABLE transactions (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, price REAL, description TEXT, date INTEGER)");
        sendMsg("Новая БД создана");
    }
}

void db::sendMsg(QString arg)
{
    emit message(arg);
}

