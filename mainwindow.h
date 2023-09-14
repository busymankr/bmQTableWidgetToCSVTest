#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* getInstance() {
        // !NOT thread safe  - first call from main only
        if (!instance)
            instance = new MainWindow();
        return instance;
    }

    bool nativeEvent(const QByteArray &type, void *vMsg, long *result);

private slots:
    void slotExport();

private:
    Ui::MainWindow *ui;
    static MainWindow* instance;
};
#endif // MAINWINDOW_H
