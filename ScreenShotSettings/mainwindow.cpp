#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    createWidgets();

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(writeSettings()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(browse, SIGNAL(clicked()), this, SLOT(selectPath()));

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addSpacing(10);
    groupBoxLayout->addWidget(new QLabel("Default filename:"));
    groupBoxLayout->addWidget(nameEdit);
    groupBoxLayout->addSpacing(20);
    groupBoxLayout->addWidget(new QLabel("Image format:"));
    groupBoxLayout->addWidget(fileExtDropdown);
    groupBoxLayout->addSpacing(25);
    groupBoxLayout->addWidget(new QLabel("Destination folder:"));
    groupBoxLayout->addWidget(pathViewer);
    groupBoxLayout->addWidget(browse);
    groupBoxLayout->addSpacing(25);

    QGroupBox *groupBox = new QGroupBox("ScreenShot Settings");
    groupBox->setLayout(groupBoxLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    loadSettings();
}

MainWindow::~MainWindow() {}

void MainWindow::createWidgets()
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    nameEdit = new QLineEdit;
    QRegExp regex("[a-zA-Z0-9_,.';-+=!@#$%^&~`]*");
    nameEdit->setValidator(new QRegExpValidator(regex, this));

    fileExtDropdown = new QComboBox;
    fileExtDropdown->setFixedWidth(80);
    fileExtDropdown->addItem(".jpg");
    fileExtDropdown->addItem(".bmp");
    fileExtDropdown->addItem(".png");
    fileExtDropdown->addItem(".GIF");

    pathViewer = new QLabel;

    browse = new QPushButton("Browse...");
    browse->setFixedWidth(80);
}

void MainWindow::loadSettings()
{
    // Load widget selections
    QSettings settings("MSF091886", "ScreenShot");
    nameEdit->setText(settings.value("defaultName").toString());
    QString fileExt = settings.value("fileExt").toString();
    fileExtDropdown->setCurrentIndex(fileExtDropdown->findText(fileExt));
    pathViewer->setText(settings.value("path").toString());

    // If the saved directory is invalid, use current directory of exe
    QDir dir;
    if (!dir.exists(pathViewer->text())) {
        pathViewer->setText(QApplication::applicationDirPath());
    }
}

bool MainWindow::writeSettings()
{
    // Save widget selections
    QSettings settings("MSF091886", "ScreenShot");
    settings.setValue("defaultName", nameEdit->text());
    settings.setValue("fileExt", fileExtDropdown->currentText());
    settings.setValue("path", pathViewer->text());

    accept();
    return true; // Probably redundant
}

void MainWindow::selectPath()
{
    QString pathStr = QFileDialog::getExistingDirectory(this, tr("Browse"),
                                                        pathViewer->text());
    if(!pathStr.isEmpty())
        pathViewer->setText(pathStr);
}
