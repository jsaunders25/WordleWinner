#include "SuggestionWidget.h"
#include "ui_SuggestionWidget.h"

#include <QStringListModel>

SuggestionWidget::SuggestionWidget(bool suggest, bool survivle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuggestionWidget)
{
    ui->setupUi(this);
    model = new QStringListModel();
    ui->listView_remaining->setModel(model);

    // ToDo: Implement better suggestion system
    ui->pushButton_another->setEnabled(false);
    Q_UNUSED(suggest) Q_UNUSED(survivle)
}

SuggestionWidget::~SuggestionWidget()
{
    delete model;
    delete ui;
}

void SuggestionWidget::setRemainingWords(QStringList words, QString lowscore_word)
{
    ui->lineEdit_suggestion->setText(lowscore_word);
    model->setStringList(words);
}

void SuggestionWidget::reset()
{
    model->setStringList(QStringList());
    ui->lineEdit_suggestion->clear();
}

/**
 * @brief SuggestionWidget::on_listView_remaining_pressed
 * When word is clicked in list, emit signal so it can be
 * populated in WordleWidget.
 * @param index
 */
void SuggestionWidget::on_listView_remaining_pressed(const QModelIndex &index)
{
        QString word = model->data(index).toString();
        if(!word.isEmpty())
            emit wordClickedSignal(word);
}

