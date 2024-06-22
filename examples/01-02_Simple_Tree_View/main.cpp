#include "mainwindow.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    // Application
    QApplication a(argc, argv);

    // Use Fusion style if Windows dark mode is enabled (Fusion is dark mode compatible)
    QSettings settings(
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        QSettings::NativeFormat);
    if (settings.value("AppsUseLightTheme") == 0)
        a.setStyle("fusion");

    // Main window
    MainWindow w;
    w.show();
    return a.exec();
}
