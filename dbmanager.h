#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class dbmanager
{
public:
    dbmanager(const QString &path);
    bool addPerson(const QString &name);
    bool personExists(const QString &name, bool found=false);
    bool removePerson(const QString &name);

    QList<QString>* printAll();

    bool removeAll();
    bool createTable();

private:

    QSqlDatabase m_db;
};
