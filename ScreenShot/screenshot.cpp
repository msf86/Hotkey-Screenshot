#include <QtGui>
#include "screenshot.h"

ScreenShot::ScreenShot(QWidget *parent)
    : QMainWindow(parent)
{
    QSettings settings("MSF091886", "ScreenShot");
    fileName = settings.value("defaultName").toString();
    filePath = settings.value("path").toString();
    format = settings.value("fileExt").toString();

    if(fileName.isEmpty()) fileName = "Screenshot";

    QDir d;
    if (!d.exists(filePath)) {

        filePath = QApplication::applicationDirPath();
    }

    if (format != ".png" &&
        format != ".jpg" &&
        format != ".bmp" &&
        format != ".GIF" )
    {
        format = ".jpg";
    }

    fileName += "_1";
    captureScreen();
}

ScreenShot::~ScreenShot() {}

void ScreenShot::captureScreen()
{
    // Capture screen
    QPixmap image = QPixmap::grabWindow(QApplication::desktop()->winId());

    // Save the image (WINDOWS ONLY)
    filePath += "\\";
    QString fullPath = filePath + fileName + format;

    QFile file(fullPath);
    while(file.exists()) {
        fileName = incrementName(fileName);
        fullPath = filePath + fileName + format;
        file.setFileName(fullPath);
    }
    image.save(fullPath);
}

QString ScreenShot::incrementName(QString &name)
{
    /* Gather the trailing number of the filename. Get it by finding the
    rightmost underbar's location, then taking the substring of everything
    to the right. */
    int pos = name.lastIndexOf("_");

    QString numStr = name.mid(pos + 1);

    // Increment the number represented in numStr
    int n = numStr.toInt();
    numStr = QString::number(n + 1);

    return fileName.left(pos + 1) + numStr;
}
