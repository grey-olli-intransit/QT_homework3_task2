#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QFile>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QCoreApplication::exit(0);
}


void MainWindow::on_pushButtonFile_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path.isEmpty()) return; // user pressed Escape or Cancel in dialogue.
    QFile htmlfile(path);
    htmlfile.open(QIODevice::ReadOnly);
    QByteArray ba = htmlfile.readAll();
    QString filecontent(ba);
    //int weatherBlockStart = filecontent.indexOf("data-testid=\"weather-temp\">",0,Qt::CaseSensitive);
    QStringList splittedHtml =filecontent.split("data-testid=\"weather-temp\">", Qt::SkipEmptyParts, Qt::CaseSensitive);
    QString weather1 = splittedHtml[1];
    QStringList splittedHtml2 = weather1.split("</span>", Qt::SkipEmptyParts, Qt::CaseSensitive);
    QString weather2 = splittedHtml2[0];
    ui->plainTextEdit->document()->setPlainText(weather2);

    splittedHtml =filecontent.split("<div class=\"rate__currency", Qt::SkipEmptyParts, Qt::CaseSensitive);
    QString rates1 = splittedHtml[1];
    splittedHtml2 = rates1.split("\">", Qt::SkipEmptyParts, Qt::CaseSensitive);
    rates1 = splittedHtml2[1];
    splittedHtml2 = rates1.split("</div>", Qt::SkipEmptyParts, Qt::CaseSensitive);
    rates1 = splittedHtml2[0];
    ui->plainTextEditRates->document()->setPlainText("Курс доллара: " + rates1);
}

