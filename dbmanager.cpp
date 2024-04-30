#include "dbmanager.h"
dbmanager::dbmanager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if(!m_db.open())
    {
        qDebug()<<"Connection to database failed";
    }
    else
    {
        qDebug() <<"Connection to database ok";
    }
    //createTable();
}
bool dbmanager::createTable() {
    QSqlQuery query;
    query.prepare("CREATE TABLE PEOPLE (name TEXT)");
    if (!query.exec()) {
        qDebug() << "Error creating table:" << query.lastError().text();
        return false;
    }
    return true;
}

bool dbmanager::addPerson(const QString &name)
{

    bool succes{false};
    QSqlQuery query;
    query.prepare("INSERT INTO PEOPLE (name) VALUES(:name)");
    query.bindValue(":name",name);
    if(query.exec())
    {
        succes = true;
        //printAll();
    }
    else
    {
        qDebug() << "add Person error:" << query.lastError().text();
    }
    return succes;
}
bool dbmanager::personExists(const QString &name, bool found )
{
    QSqlQuery query;
    query.prepare("SELECT name FROM people WHERE name = (:name)");
    query.bindValue(":name",name);
    if(query.exec())
    {
        if(query.next())
        {
            found=true;
        }
    }else
    {
        qDebug() <<"PersonExists error :" << query.lastError().text();
    }
    return found;
}
bool dbmanager::removePerson(const QString& name)
{
    bool success = false;
    if(personExists(name))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
        queryDelete.bindValue(":name",name);
        success = queryDelete.exec();
        if(!success)
        {
            qDebug()<<"remove person failed";
        }
            //else
            //printAll();
    }
    else
    {
        qDebug()<<"person doesn't exist";
    }
    return success;
}
QList<QString>* dbmanager::printAll()
{
    QList<QString>* names = new QList<QString>;
    qDebug() <<"People in db:";
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while(query.next())
    {
        QString name = query.value(idName).toString();
        names->append(name);
        qDebug()<<"==="<<name;
    }
    return names;
}
bool dbmanager::removeAll()
{
    bool success = false;
    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM PEOPLE");
    if(removeQuery.exec())
    {
        success = true;
        //printAll();
    }
    else
    {
        qDebug() << "remove failed "<< removeQuery.lastError();
    }
    return success;
}
