#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent) : QMainWindow(parent), ui(new Ui::Tasky)
{
    ui->setupUi(this);

    clean();
    ui->TblWorks->setColumnCount(4);
    QStringList head;
    head << "Signa" << "Name" << "Date" << "Hour";
    ui->TblWorks->setHorizontalHeaderLabels(head);

    charge();

    // Conexión de la señal 'clicked' del botón usando la nueva sintaxis
}

Tasky::~Tasky()
{
    delete ui;
}

void Tasky::on_BtnAdd_clicked()
{
    QString name = ui->TxWork->text().trimmed(); // Trim para eliminar espacios al inicio y al final

    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Agregar tarea", "El campo de tarea no puede estar vacío");
        ui->TxWork->setFocus(); // Poner el foco en el campo de tarea
        return;
    }

    QString sign = ui->BoxMat->currentText();
    QDate date = ui->Eddate->date();
    QTime hour = ui->Edtime->time();

    Tarea *t = new Tarea(sign, name, date, hour);
    agregarTarea(t);

    clean();
    save();

    qDebug() << "Tarea agregada y guardada correctamente.";
}

void Tasky::agregarTarea(Tarea *t)
{
    m_tareas.append(t);

    int fila = ui->TblWorks->rowCount();
    ui->TblWorks->insertRow(fila);

    ui->TblWorks->setItem(fila, TAREA, new QTableWidgetItem(t->name()));
    ui->TblWorks->setItem(fila, ASIGNATURA, new QTableWidgetItem(t->signa()));
    ui->TblWorks->setItem(fila, FECHA, new QTableWidgetItem(t->date().toString("dd/MM/yy")));
    ui->TblWorks->setItem(fila, HORA, new QTableWidgetItem(t->hour().toString("hh:mm")));

    // Calcula el tiempo restante en segundos
      qint64 segundosRestantes = QDateTime::currentDateTime().secsTo(QDateTime(t->date(), t->hour()));

      // Define el formato de colores
      if (segundosRestantes < 24 * 60 * 60) {  // Menos de un día
          ui->TblWorks->item(fila, TAREA)->setBackgroundColor(Qt::red);
          ui->TblWorks->item(fila, ASIGNATURA)->setBackgroundColor(Qt::red);
          ui->TblWorks->item(fila, FECHA)->setBackgroundColor(Qt::red);
          ui->TblWorks->item(fila, HORA)->setBackgroundColor(Qt::red);
      } else {
          ui->TblWorks->item(fila, TAREA)->setBackgroundColor(Qt::green);
          ui->TblWorks->item(fila, ASIGNATURA)->setBackgroundColor(Qt::green);
          ui->TblWorks->item(fila, FECHA)->setBackgroundColor(Qt::green);
          ui->TblWorks->item(fila, HORA)->setBackgroundColor(Qt::green);
      }
}

void Tasky::clean()
{
    QDate hoy = QDate::currentDate();
    QTime now = QTime::currentTime();
    ui->Eddate->setMinimumDate(hoy);
    ui->Eddate->setDate(hoy);
    ui->Edtime->setTime(now);

    ui->TxWork->clear();
    ui->BoxMat->setCurrentIndex(0);

    ui->TxWork->setFocus();
}

void Tasky::save()
{
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream salida(&archivo);
        foreach (Tarea *t, m_tareas)
        {
            salida << t->name() << ";" << t->signa() << ";"
                   << t->date().toString("dd/MM/yy") << ";"
                   << t->hour().toString("hh:mm") << "\n";
        }
        archivo.close();
        QMessageBox::information(this, "Agregar Tarea", "Tarea guardada con éxito");
    }
    else
    {
        QMessageBox::critical(this, "Guardar Tareas", "No se puede escribir sobre " + ARCHIVO);
    }
}

void Tasky::charge()
{
    QFile archivo(ARCHIVO);
    if (!archivo.exists())
        return;

    if (archivo.open(QFile::ReadOnly))
    {
        QTextStream entrada(&archivo);
        while (!entrada.atEnd())
        {
            QStringList datos = entrada.readLine().split(";");
            if (datos.size() == 4)
            {
                QString name = datos[0];
                QString sign = datos[1];
                QDate date = QDate::fromString(datos[2], "dd/MM/yy");
                QTime hour = QTime::fromString(datos[3], "hh:mm");

                Tarea *t = new Tarea(sign, name, date, hour);
                agregarTarea(t);
            }
        }
        archivo.close();
    }
}

void Tasky::on_BtnDelete_clicked()
{
    int filaSeleccionada = ui->TblWorks->currentRow();
    if (filaSeleccionada >= 0)
    {
        eliminarTarea(filaSeleccionada);
        save();
        QMessageBox::information(this, "Eliminar Tarea", "Tarea eliminada con éxito");
    }
    else
    {
        QMessageBox::warning(this, "Eliminar Tarea", "Seleccione una tarea para eliminar");
    }
}

void Tasky::eliminarTarea(int fila)
{
    if (fila >= 0 && fila < m_tareas.size())
    {
        delete m_tareas.takeAt(fila);
        ui->TblWorks->removeRow(fila);
    }
}



