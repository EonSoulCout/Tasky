#include "tarea.h"

const QString &Tarea::signa() const
{
    return m_signa;
}

void Tarea::setSigna(const QString &newSigna)
{
    m_signa = newSigna;
}

const QString &Tarea::name() const
{
    return m_name;
}

void Tarea::setName(const QString &newName)
{
    m_name = newName;
}

const QDate &Tarea::date() const
{
    return m_date;
}

void Tarea::setDate(const QDate &newDate)
{
    m_date = newDate;
}

const QTime &Tarea::hour() const
{
    return m_hour;
}

void Tarea::setHour(const QTime &newHour)
{
    m_hour = newHour;
}

Tarea::Tarea(const QString &signa, const QString &name, const QDate &date, const QTime &hour) : m_signa(signa),
    m_name(name),
    m_date(date),
    m_hour(hour)
{}
