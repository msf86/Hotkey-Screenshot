#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QDialog>

class QDialogButtonBox;
class QPushButton;
class QLabel;
class QComboBox;
class QLineEdit;

class MainWindow : public QDialog
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadSettings();
    void createWidgets();

private slots:
    bool writeSettings();
    void selectPath();

private:
    QDialogButtonBox *buttonBox;
    QLineEdit *nameEdit;
    QComboBox *fileExtDropdown;
    QLabel *pathViewer;
    QPushButton *browse;
};

#endif // MAINWINDOW_H
