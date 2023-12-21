#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasky)
{
    ui->setupUi(this);
    //Actualiza hora y fecha y valida
    QDate hoy = QDate::currentDate();
    QTime now = QTime::currentTime();
    ui->Eddate->setMinimumDate(hoy);
    ui->Eddate->setDate(hoy);
    ui->Edtime->setTime(now);

    ui->TblWorks->setColumnCount(4);
    QStringList head;
    head << "Signa" << "Name" << "Date" << "Hour";
    ui->TblWorks->setHorizontalHeaderLabels(head);


    //permite crear la intefaz grafica
}

Tasky::~Tasky()
{
    delete ui;
}


void Tasky::on_Btnadd_clicked()
{
    QString name = ui->TxWork->text();
    QString sign = ui->BoxMat->currentText();
    QDate date = ui->Eddate->date();
    QTime hour = ui->Edtime->time();

    ui->TblWorks->insertRow(ui->TblWorks->rowCount());
    int fila=ui->TblWorks->rowCount()-1;
    //ui->TblWorks->setItem(fila, name, new QTableWidgetItem(name));
    //ui->TblWorks->setItem(fila, sign, new QTableWidgetItem(sign));
    //ui->TblWorks->setItem(fila, date, new QTableWidgetItem(QDate::getDate(date)));
    //ui->TblWorks->setItem(fila, hour, new QTableWidgetItem(QDate::));

    m_tareas.append(new Tarea(sign, name, date, hour));

}

