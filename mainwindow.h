#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <db.h>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    db *data;
    void cleanForm();
private slots:
    void statusMsg(QString arg);
    void on_pushButton_clicked();
    void on_lineMoneyOff_editingFinished();
    void on_editMoney_editingFinished();
    void on_editMoney_valueChanged(double arg1);
    void initCombo();
    void drawTable();
    void drawTableItems(int period);
    void on_comboDatesAgo_activated(int index);
};

#endif // MAINWINDOW_H
