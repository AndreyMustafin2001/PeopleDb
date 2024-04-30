#include "graphic.h"

graphic::graphic(QWidget *parent)
    : QWidget{parent}
{
    level = 0;
    const QString &path = "D:/Work/Qtcreator/dbmanager/people.db";
    BasLurman = new dbmanager(path);

    QVBoxLayout *Box = new QVBoxLayout;
    QVBoxLayout *firstHalf = new QVBoxLayout();
    QHBoxLayout *ff = new QHBoxLayout();
    QHBoxLayout *fv = new QHBoxLayout();

    lineEdit = new QLineEdit(this);
    lineEdit->setStyleSheet("background-color: #FFFAFA;");
    QFont font("Arial", 11);
    lineEdit->setFont(font);
    lineEdit->setFixedSize(470,20);
    ff->addWidget(lineEdit);

    QPushButton *add = new QPushButton("+",this);add->setFixedSize(65,50);fv->addWidget(add);
    QPushButton *remove = new QPushButton("-",this);remove->setFixedSize(65,50);fv->addWidget(remove);
    QPushButton *removeAll = new QPushButton("removeAll",this);removeAll->setFixedSize(65,50);fv->addWidget(removeAll);
    QPushButton *personExist = new QPushButton("Exists",this);personExist->setFixedSize(65,50);fv->addWidget(personExist);
    QPushButton *printAll = new QPushButton("printAll",this);printAll->setFixedSize(65,50);fv->addWidget(printAll);

    add->setFont(font);
    remove->setFont(font);
    removeAll->setFont(font);
    personExist->setFont(font);
    printAll->setFont(font);

    QWidget *w_ff = new QWidget();w_ff->setLayout(ff);
    QWidget *w_fv = new QWidget(); w_fv->setLayout(fv);

    firstHalf->addWidget(w_ff);
    firstHalf->addWidget(w_fv);

    QScrollArea *secondHalf = new QScrollArea;
    List = new QVBoxLayout;

    QWidget *Try = new QWidget;

    List->addStretch(1);
    Try->setLayout(List);

    secondHalf->setWidget(Try);
    secondHalf->setWidgetResizable(true);

    QWidget *tmp = new QWidget();
    tmp->setLayout(firstHalf);
    Box->addWidget(tmp);
    Box->addWidget(secondHalf);
    setLayout(Box);
    tmp->setStyleSheet("background-color: #696969;");
    secondHalf->setStyleSheet("background-color: #696969;");

    connect (add,&QPushButton::clicked,this,&graphic::Add);
    connect (remove,&QPushButton::clicked,this,&graphic::Remove);
    connect (removeAll,&QPushButton::clicked,this,&graphic::RemoveAll);
    connect (personExist,&QPushButton::clicked,this,&graphic::Exists);
    connect (printAll,&QPushButton::clicked,this,&graphic::PrintAll);

    add->setStyleSheet("background-color: #ADFF2F;");
    remove->setStyleSheet("background-color: #DC143C;");
    removeAll->setStyleSheet("background-color: #E0FFFF;");
    personExist->setStyleSheet("background-color: #5F9EA0;");
    printAll->setStyleSheet("background-color: #F0E68C;");
}
void graphic::PrintAll()
{
    deleteTextEdit("");
    QList<QString>*names = BasLurman->printAll();
    for (int i=0;i<names->size();i++)
    {
        addTextEdit(names->at(i));
    }
}
void graphic::Exists()
{
    QString name = lineEdit->text();
    QString answer;
    if(BasLurman->personExists(name))
    {
        answer = "Person Exists!";
    }
    else
        answer = "Person doesn't Exist!";

    QDialog *dialog = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    dialog->setWindowTitle("o_O");
    QTextEdit *textEdit = new QTextEdit;

    textEdit->setReadOnly(true);
    textEdit->setFixedSize(100, 40);
    textEdit->setAlignment(Qt::AlignCenter);
    textEdit->setPlainText(answer);

    layout->addWidget(textEdit);
    layout->setAlignment(Qt::AlignCenter);
    dialog->setLayout(layout);
    dialog->show();
}
void graphic::Add()
{
    const QString &name = lineEdit->text();
    BasLurman->addPerson(name);
    addTextEdit(name);
}
void graphic::Remove()
{
    const QString &name = lineEdit->text();
    BasLurman->removePerson(name);
    deleteTextEdit(name);
}
void graphic::RemoveAll()
{
    BasLurman->removeAll();
    deleteTextEdit("");
}
void graphic::addTextEdit(QString name)
{
    QFont font ("Arial",11);
    if(name.isEmpty())return;
    QHBoxLayout *oba  =new QHBoxLayout;
    QLabel *lbl = new QLabel(QString("%1.").arg(level+1));
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setStyleSheet("background-color: #FFFAFA;");
    lbl->setStyleSheet("background-color: #FFFAFA;");
    textEdit->setFixedSize(200,27);
    textEdit->setFont(font);
    textEdit->insertPlainText(name);
    textEdit->setReadOnly(true);

    oba->addWidget(lbl);
    oba->addWidget(textEdit);
    oba->addStretch(1);

    QWidget *tmp =new QWidget;
    tmp->setLayout(oba);
    List->insertWidget(level,tmp);
    level++;
    textEdits.append(textEdit);
    labels.append(lbl);
    layouts.append(tmp);
    textEdit->show();
}
void graphic::deleteTextEdit(const QString& targetText)
{
    bool flag = true;
    for (int i = 0; i < textEdits.size(); ) {
        QTextEdit *textEdit = textEdits.at(i);

        QLabel *l = labels.at(i);

        QWidget *box = layouts.at(i);

        if (flag && textEdit->toPlainText() == targetText || targetText.isEmpty())
        {
            textEdits.removeAt(i);
            labels.removeAt(i);
            layouts.removeAt(i);
            List->removeWidget(box);
            textEdit->deleteLater();
            l->deleteLater();
            box->deleteLater();

            level--;
            flag = false;
        }
        else
            i++;
        l->setText(QString("%1.").arg(i));
    }
}
