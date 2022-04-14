#ifndef WORDLEEDIT_H
#define WORDLEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class WordleEdit : public QLineEdit
{
    Q_OBJECT
public:
    WordleEdit();

public slots:
    void takeFocus();

signals:
    void doneSignal();  // emit when valid character is entered

private slots:
    void capitalize(const QString str);
    void validateText(const QString str);

};

#endif // WORDLEEDIT_H
