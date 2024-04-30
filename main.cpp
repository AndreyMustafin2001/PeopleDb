#include "graphic.h"
//#include "dbmanager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    graphic a;
    //a.setFixedSize(1000,1000);
    a.resize(500,500);
    a.setWindowTitle("People DataBase");
    a.show();

    return app.exec();
}
