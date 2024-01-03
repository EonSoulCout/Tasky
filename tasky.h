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
    void on_BtnAdd_clicked(); // Renombrado para seguir la convención de nombres
    void on_BtnDelete_clicked();

private:
    Ui::Tasky *ui;
    QList <Tarea*> m_tareas;
    const QString ARCHIVO = "Tareas.csv";
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
    void eliminarTarea(int fila);

    // Agrega una nueva señal en la sección de señales privadas de tu clase Tasky
signals:
    void tareaEliminada(int fila);

};
#endif // TASKY_H
