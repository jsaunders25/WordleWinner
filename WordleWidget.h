#ifndef WORDLEWIDGET_H
#define WORDLEWIDGET_H

#include <QWidget>

namespace Ui {
class WorldeWidget;
}
class QComboBox;

class WordleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordleWidget(QWidget *parent = nullptr);
    ~WordleWidget();
    void reset();
    void useWord(QString word);

signals:
    void submitWord(QString, int[5]);

private slots:
    void on_lineEdit_1_textEdited(const QString &arg1);
    void on_lineEdit_2_textEdited(const QString &arg1);
    void on_lineEdit_3_textEdited(const QString &arg1);
    void on_lineEdit_4_textEdited(const QString &arg1);
    void on_lineEdit_5_textEdited(const QString &arg1);

    void on_pushButton_submit_clicked();


private:
    Ui::WorldeWidget *ui;
    bool validateLineEdits(QString str);
    void populateComboBoxes();
    void populateComboBox(QComboBox *cb);

    const QStringList hints = QStringList({"Green", "Yellow", "Grey"});
};

#endif // WORDLEWIDGET_H
