#ifndef TASKY_H
#define TASKY_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#include <tarea.h>


QT_BEGIN_NAMESPACE
namespace Ui { class Tasky; }
QT_END_NAMESPACE

class Tasky : public QMainWindow
{
    Q_OBJECT

public:
    Tasky(QWidget *parent = nullptr);
    ~Tasky();

private slots:
    void on_Btnadd_clicked();

private:
    Ui::Tasky *ui;
    QList <Tarea*> m_tareas;
    const QString ARCHIVO ="Tares.csv";
    /*
    -Archivos CSV
    -Archivod de texto
    -Para guar datos por campos
    -Cada linea es un resgistro
    -Cada dato se separa por comas (,)
    */

    enum Col{
        TAREA,ASIGNATURA,FECHA,HORA
    };

    void agregarTarea(Tarea *t);
    void clean();
    void save();
    void charge();
};
#endif // TASKY_H
