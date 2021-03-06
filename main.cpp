#include <GlobalNames.h>
#include <MainWindow/MainWindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication Application(argc, argv);

    QCoreApplication::setApplicationName(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_NAME);
    QCoreApplication::setOrganizationDomain(GLOBAL_STRINGS::PROGRAM_INFO::ORGANIZATION_NAME);
    QCoreApplication::setApplicationVersion(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_VERSION);

    MainWindow ApplicationWindow;
    ApplicationWindow.show();

    return Application.exec();
}
