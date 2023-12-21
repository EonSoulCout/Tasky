#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent): QMainWindow(parent), ui(new Ui::Tasky)
{
    ui->setupUi(this);

    clean();
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

    if(name.length() == 0){
        QMessageBox::warning(this, "Agregar tarea", "El campo de tarea no puede estar vacio");
        return;
        ui->TxWork->setFocus();
    }

    QString sign = ui->BoxMat->currentText();
    QDate date = ui->Eddate->date();
    QTime hour = ui->Edtime->time();

    Tarea *t= new Tarea(sign, name, date, hour);
    agregarTarea(t);

    clean();

    save();

}

void Tasky::agregarTarea(Tarea *t)
{
    m_tareas.append(t);

    int fila=ui->TblWorks->rowCount();

    ui->TblWorks->insertRow(fila);

    ui->TblWorks->setItem(fila, TAREA, new QTableWidgetItem(t->name()));
    ui->TblWorks->setItem(fila, ASIGNATURA, new QTableWidgetItem(t->signa()));
    ui->TblWorks->setItem(fila, FECHA, new QTableWidgetItem(t->date().toString("dd/MM/yy")));
    ui->TblWorks->setItem(fila, HORA, new QTableWidgetItem(t->hour().toString("hh:mm")));

}

void Tasky::clean()
{
    //Actualiza hora y fecha y valida
    QDate hoy = QDate::currentDate();
    QTime now = QTime::currentTime();
    ui->Eddate->setMinimumDate(hoy);
    ui->Eddate->setDate(hoy);
    ui->Edtime->setTime(now);

    //limpia campos
    ui->Eddate->clear();
    ui->BoxMat->setCurrentIndex(0);

    //setea (Reinicia el foco) lo mueve al campo de tarea
    ui->TxWork->setFocus();
}

void Tasky::save()
{
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);
        Tarea *t;
        foreach(t, m_tareas){
            salida << t->name() << ";" << t->signa() << ";";
            salida << t->date().toString("dd/MM/yy") << ";";
            salida << t->hour().toString("hh:mm") << "\n";
        }
        /*for (int i=0; i<filas; i++) {
            QTableWidgetItem *name = ui->TblWorks->item(i, name);
            QTableWidgetItem *signa = ui->TblWorks->item(i, APELLIDO);
            QTableWidgetItem *date = ui->TblWorks->item(i, TELEFONO);
            QTableWidgetItem *hour = ui->TblWorks->item(i, EMAIL);
            salida << nombre->text() << ";" << apellido->text() << ";";
            salida << telefono->text() << ";" << email->text() << "\n";
        }*/
        archivo.close();
        QMessageBox::information(this,"aGREGADA Tarea","Tarea guardada con éxito");
    }else{
        QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO);
    }
}

