#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <QDebug>

class QMdiSubWindow;
class ChildWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool openFile(const QString &fileName);
    void init();
private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();

    void on_actionTestbutton_triggered();

private:
    Ui::MainWindow *ui;
    int fileIndex;
    bool loadFile(const QString &fileName);
    QMdiSubWindow *findChildWindow(const QString &fileName) const;
    ChildWindow *currentChildWindow() const;
    void functionUpdate();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
