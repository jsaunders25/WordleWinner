#ifndef WORDLEWIDGET_H
#define WORDLEWIDGET_H

#include <QWidget>

namespace Ui {
class WorldeWidget;
}
class QComboBox;
class WordleEdit;
class QHBoxLayout;

class WordleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordleWidget(QWidget *parent = nullptr);
    ~WordleWidget();
    void deleteAll();
    void reset();
    void configure(int length, int count);
    void useWord(QString word);

signals:
    void submitWord(QString, QList<QList<int>>);

private slots:
    void on_pushButton_submit_clicked();


private:
    Ui::WorldeWidget *ui;
    void connectLineEdits();

    const QStringList hint_list = QStringList({"Green", "Yellow", "Grey"});
    QList<WordleEdit*> line_edits;   // line edits for entering letters
    QList<QComboBox*> combo_boxes;  // combo boxes for hints
    QList<QHBoxLayout*> cb_layouts; // horizontal layouts that hold combo boxes
};

#endif // WORDLEWIDGET_H
