#ifndef SUGGESTIONWIDGET_H
#define SUGGESTIONWIDGET_H

#include <QWidget>

namespace Ui {
class SuggestionWidget;
}
class QStringListModel;
class SuggestionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SuggestionWidget(bool suggest, bool survivle, QWidget *parent = nullptr);
    ~SuggestionWidget();

    void setRemainingWords(QStringList words, QString lowscore_word);
    void reset();

signals:
    void wordClickedSignal(QString);

private slots:
    void on_listView_remaining_pressed(const QModelIndex &index);

private:
    Ui::SuggestionWidget *ui;
    QStringListModel *model;
};

#endif // SUGGESTIONWIDGET_H
