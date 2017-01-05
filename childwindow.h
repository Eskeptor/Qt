#ifndef CHILDWINDOW
#define CHILDWINDOW

#include <QPlainTextEdit>
#include <QString>

class ChildWindow : public QPlainTextEdit
{
    Q_OBJECT

public:
    ChildWindow();

    void newFile(int idx);
    void thisWindowTextChanged();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    QString getCurFile();
private:
    QString curFile;
    bool isUntitle;
    bool saveQuestion();
    void setCurFile(const QString &fileName);
    QString currentFileName();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CHILDWINDOW
