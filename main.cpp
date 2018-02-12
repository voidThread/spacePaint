#include "MainWindow/MainWindow.h"
#include <QApplication>

#include "GlobalNames.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(spacePaint);

    QApplication Application(argc, argv);

    QCoreApplication::setApplicationName(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_NAME);
    QCoreApplication::setOrganizationDomain(GLOBAL_STRINGS::PROGRAM_INFO::ORGANIZATION_NAME);
    QCoreApplication::setApplicationName(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_VERSION);

    MainWindow ApplicationWindow;
    ApplicationWindow.show();

    return Application.exec();
}
