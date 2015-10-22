#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cleanForm();
    setWindowTitle("Книга затрат");
    data = new db();
    connect(data,SIGNAL(message(QString)),this,SLOT(statusMsg(QString)));
    initCombo();
    drawTable();
    //drawTableItems(6);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cleanForm()
{
    ui->editDescription->setText("");
    ui->editMoney->setValue(0.0);
}

void MainWindow::statusMsg(QString arg)
{
    ui->statusBar->showMessage(arg, 3000);
}

void MainWindow::on_pushButton_clicked()
{
    data->addTransaction(ui->editMoney->value(), ui->editDescription->text());
    cleanForm();
}

void MainWindow::on_lineMoneyOff_editingFinished()
{

}

void MainWindow::on_editMoney_editingFinished()
{

}

void MainWindow::on_editMoney_valueChanged(double arg1)
{
    if(arg1 < 0)
    {
        ui->editDescription->setPlaceholderText("На что потрачено?");
    }
    else
    {
        ui->editDescription->setPlaceholderText("Откуда или за что получены?");
    }
}

void MainWindow::initCombo()
{
    QStringList dates;
    dates.append("Cегодня");
    dates.append("Вчера");
    dates.append("Неделя");
    dates.append("Месяц");
    dates.append("3 месяца");
    dates.append("Год");
    dates.append("Все время");
    ui->comboDatesAgo->addItems(dates);
    ui->comboDatesAgo->setCurrentIndex(6);
}

void MainWindow::drawTable()
{
    ui->tableTransactions->setColumnCount(3);
    QStringList list;
    list << "Деньги" << "Описание" << "Дата";
    ui->tableTransactions->setHorizontalHeaderLabels(list);
    ui->tableTransactions->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void MainWindow::drawTableItems(int period)
{
    QSqlQuery *qr;
    qr = data->result();
    int cortage = 0;
    qint64 dt, topDt;
    QDate tmpd;
    QDateTime tmpdd;
    topDt = QDateTime::currentMSecsSinceEpoch();
    switch(period)
    {
    case 0:
        tmpdd.setDate(QDate::currentDate());
        dt = tmpdd.toMSecsSinceEpoch();
        break; // Данные за вчера
    case 1:
        tmpdd.setDate(QDate::currentDate().addDays(-1));
        dt = tmpdd.toMSecsSinceEpoch();
        tmpdd.setDate(QDate::currentDate());
        topDt = tmpdd.toMSecsSinceEpoch();
        break; // Данные за вчера
    case 2:
        tmpdd.setDate(QDate::currentDate().addDays(-7));
        dt = tmpdd.toMSecsSinceEpoch();
        break; // Данные за неделю
    case 3:
        tmpdd.setDate(QDate::currentDate().addMonths(-1));
        dt = tmpdd.toMSecsSinceEpoch();
        break; // Данные за месяц
    case 4:
        tmpdd.setDate(QDate::currentDate().addMonths(-3));
        dt = tmpdd.toMSecsSinceEpoch();
        break; // Данные за 3 месяца
    case 5:
        tmpdd.setDate(QDate::currentDate().addYears(-1));
        dt = tmpdd.toMSecsSinceEpoch();
        break; // Данные за год

    case 6:
        dt = 0;
        break; // За всё время

    default:
        dt = 0;
        break;

    }

    ui->tableTransactions->setRowCount(0);
    ui->transactionsFor->setText(QDateTime::fromMSecsSinceEpoch(dt).toString("d-M-yy"));
    ui->transactionsForTop->setText(QDateTime::fromMSecsSinceEpoch(topDt).toString("d-M-yy"));
    while(qr->next())
    {
        if( (qr->value(3).toLongLong() >= dt) && (qr->value(3).toLongLong() < topDt))
        {
            qint64 dateTrans = qr->value(3).toLongLong();

            ui->tableTransactions->insertRow(ui->tableTransactions->rowCount());
            ui->tableTransactions->setItem(cortage, 0, new QTableWidgetItem(qr->value(1).toString()));
            ui->tableTransactions->setItem(cortage, 1, new QTableWidgetItem(qr->value(2).toString()));
            ui->tableTransactions->setItem(cortage, 2, new QTableWidgetItem(QDateTime::fromMSecsSinceEpoch(dateTrans).toString("d-M-yy")));
            cortage++;
        }
    }
}

void MainWindow::on_comboDatesAgo_activated(int index)
{
    drawTableItems(index);
}
