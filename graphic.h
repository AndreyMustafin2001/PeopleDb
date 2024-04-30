#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QTextEdit>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <QDialog>
#include <QDir>
#include "dbmanager.h"

class graphic : public QWidget
{
    Q_OBJECT
public:
    graphic(QWidget *parent = 0);

private slots:
    void Add();
    void Remove();
    void RemoveAll();
    void addTextEdit(QString name);
    void deleteTextEdit(const QString& targetText);
    void Exists();
    void PrintAll();

private:

    QLineEdit *lineEdit;
    QLineEdit *Table;
    dbmanager *BasLurman;
    QGridLayout *grid;
    QList<QTextEdit*> textEdits;
    QList<QLabel*> labels;
    QList<QWidget*> layouts;
    QVBoxLayout *List;
    int level;
};


