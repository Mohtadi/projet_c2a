#include <QApplication>

#include "main_window.h"


int main( int argc, char ** argv )
{
    //Pour avoir les accents
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication application( argc, argv );

    CMainWindow main_window (argc , argv);

    main_window.show();
//Commentaire 1
    return application.exec();
}

