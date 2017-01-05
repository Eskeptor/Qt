#include "childwindow.h"
#include <QtWidgets>

ChildWindow::ChildWindow()
{
    //setAttribute(Qt::WA_DeleteOnClose);
    isUntitle = true;
}

void ChildWindow::newFile(int idx)
{
    isUntitle = true;
    curFile = trUtf8("new File%1").arg(idx);
    setWindowTitle(curFile);
    //document()->setModified(false);
    connect(document(), &QTextDocument::contentsChanged, this, &ChildWindow::thisWindowTextChanged);
}

void ChildWindow::thisWindowTextChanged()
{
    setWindowModified(document()->isModified());
}

bool ChildWindow::saveQuestion()
{
    if(!document()->isModified())
    {
        return true;
    }
    const QMessageBox::StandardButton question = QMessageBox::warning(this, trUtf8("Warning"), trUtf8("'%1' has been changed. \nDo you want to save this file?").arg(currentFileName()), QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
    switch (question) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Discard:
        return true;
    case QMessageBox::Cancel:
        return false;
    default:
        return false;
    }
}

QString ChildWindow::currentFileName()
{
    return QFileInfo(curFile).fileName();
}

bool ChildWindow::save()
{
    if(isUntitle)
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool ChildWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, trUtf8("Save As"), curFile);
    if(fileName.isEmpty())
    {
        return false;
    }
    return saveFile(fileName);
}

bool ChildWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        if(!file.exists())
        {
            QMessageBox::warning(this, trUtf8("Error"), trUtf8("Not exist file!"));
            return false;
        }
        else
        {
            QMessageBox::warning(this, trUtf8("Error"), trUtf8("Can't write file!"));
            return false;
        }
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurFile(fileName);
    return true;
}

bool ChildWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        if(!file.exists())
        {
            QMessageBox::warning(this, trUtf8("Error"), trUtf8("Not exist file!"));
            return false;
        }
        else
        {
            QMessageBox::warning(this, trUtf8("Error"), trUtf8("Can't read file!"));
            return false;
        }
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurFile(fileName);

    connect(document(), &QTextDocument::contentsChanged, this, &ChildWindow::thisWindowTextChanged);

    return true;
}

void ChildWindow::setCurFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitle = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(currentFileName() + "[*]");
}

QString ChildWindow::getCurFile()
{
    return curFile;
}

void ChildWindow::closeEvent(QCloseEvent *event)
{
    if(saveQuestion())
    {
        document()->setModified(false);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
