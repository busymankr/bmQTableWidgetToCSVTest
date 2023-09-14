#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow* MainWindow::instance = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(geometry().width(), geometry().height());

    connect(ui->btnExport, SIGNAL(clicked()), this, SLOT(slotExport()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotExport()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Select file"), QString(tr("%1")).arg(QApplication::applicationDirPath()));
    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if (false == file.open(QIODevice::ReadWrite))
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromUtf8("Cannot open the %1 file.").arg(filename));
        msgBox.exec();
        return;
    }

    QTextStream stream(&file);

    QString tmp = "";
    QStringList valList;
    for (int j = 0; j < ui->tableWidget->columnCount(); j++)
    {
        QTableWidgetItem *w = ui->tableWidget->horizontalHeaderItem(j);
        if (nullptr != w)
        {
            tmp = w->text();
        }
        else
        {
            tmp = "";
        }

        valList.append("\"" + tmp + "\"");
    }

    qDebug() << valList.join(",");
    stream << valList.join(",") << "\n";

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        valList.clear();
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *w = ui->tableWidget->item(i, j);
            if (nullptr != w)
            {
                tmp = w->text();
            }
            else
            {
                tmp = "";
            }
            valList.append("\"" + tmp + "\"");
        }

        qDebug() << valList.join(",");
        stream << valList.join(",") << "\n";
    }
}

bool MainWindow::nativeEvent(const QByteArray &type, void *vMsg, long *result)
{
    Q_UNUSED(type);
    Q_UNUSED(vMsg);

    // end of if msg->message
    *result = 0; //get rid of obnoxious compiler warning

    return false; // let qt handle the rest
}
