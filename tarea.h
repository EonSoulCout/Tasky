#ifndef TAREA_H
#define TAREA_H

#include <QObject>
#include <QDate>

class Tarea : public QObject
{
    Q_OBJECT
private:
    QString m_signa;
    QString m_name;
    QDate m_date;
    QTime m_hour;
public:
    explicit Tarea(QObject *parent = nullptr);
    Tarea(const QString &signa, const QString &name, const QDate &date, const QTime &hour);

    const QString &signa() const;
    void setSigna(const QString &newSigna);
    const QString &name() const;
    void setName(const QString &newName);
    const QDate &date() const;
    void setDate(const QDate &newDate);
    const QTime &hour() const;
    void setHour(const QTime &newHour);

signals:

};

#endif // TAREA_H
