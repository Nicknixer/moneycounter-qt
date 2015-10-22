#ifndef DB_H
#define DB_H

#include <QObject>
#include <QFile>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>


class db : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase *data;
    void connect();
    void sendMsg(QString arg);
    QSqlQuery *res;
public:
    explicit db(QObject *parent = 0);
    void addTransaction(double price, QString desc);
    QSqlQuery *result();
signals:
    void message(QString arg);
public slots:
};

#endif // DB_H
