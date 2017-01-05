#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "childwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    fileIndex = 1;
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);

    ui->actionNew->triggered(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();
    if(ui->mdiArea->currentSubWindow())
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

bool MainWindow::openFile(const QString &fileName)
{
    if(QMdiSubWindow *existedWindow = findChildWindow(fileName))
    {
        ui->mdiArea->setActiveSubWindow(existedWindow);
        return true;
    }
    const bool successed = loadFile(fileName);

    return successed;
}

bool MainWindow::loadFile(const QString &fileName)
{
    ChildWindow *child = new ChildWindow;
    ui->mdiArea->addSubWindow(child);
    const bool succeeded = child->loadFile(fileName);

    if (succeeded)
    {
        child->show();
    }
    else
    {
        child->close();
    }

    return succeeded;
}

ChildWindow *MainWindow::currentChildWindow() const
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
    {
        return qobject_cast<ChildWindow *>(activeSubWindow->widget());
    }

    return 0;
}

QMdiSubWindow *MainWindow::findChildWindow(const QString &fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        ChildWindow *childwindow = qobject_cast<ChildWindow *>(window->widget());
        if (childwindow->getCurFile() == canonicalFilePath)
        {
            return window;
        }
    }
    return 0;
}

void MainWindow::functionUpdate()
{
    bool childSelection = (currentChildWindow() && currentChildWindow()->document()->isModified());
    ui->actionCut->setEnabled(childSelection);
    ui->actionCopy->setEnabled(childSelection);
    ui->actionPaste->setEnabled(childSelection);
}

void MainWindow::on_actionNew_triggered()
{
    ChildWindow *child = new ChildWindow;

    ui->mdiArea->addSubWindow(child);
    child->newFile(fileIndex++);
    child->showMaximized();
    child->show();

    connect(child->document(), &QTextDocument::contentsChanged, this, &MainWindow::functionUpdate);

}

void MainWindow::on_actionSave_triggered()
{
    if(currentChildWindow() && currentChildWindow()->save());
}

void MainWindow::on_actionSave_As_triggered()
{
    if(currentChildWindow() && currentChildWindow()->saveAs());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    if(!fileName.isEmpty())
    {
        openFile(fileName);
    }
}

void MainWindow::on_actionCut_triggered()
{
    if(currentChildWindow())
    {
        currentChildWindow()->cut();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    if(currentChildWindow())
    {
        currentChildWindow()->copy();
    }
}

void MainWindow::on_actionPaste_triggered()
{
    if(currentChildWindow())
    {
        currentChildWindow()->paste();
    }
}

void MainWindow::on_actionTestbutton_triggered()
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
    {
        qDebug() << "child detect";
    }
    else
    {
        qDebug() << "detect fail";
    }
}
