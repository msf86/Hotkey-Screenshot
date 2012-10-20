#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QtGui/QMainWindow>

class ScreenShot : public QMainWindow
{
    Q_OBJECT
    
public:
    ScreenShot(QWidget *parent = 0);
    ~ScreenShot();

private:
    QString fileName;
    QString filePath;
    QString format;
    QPixmap pic;
    void captureScreen();
    QString incrementName(QString& name);
};

#endif // SCREENSHOT_H
