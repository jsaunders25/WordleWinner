#include "WordleWidget.h"
#include "ui_WordleWidget.h"
#include "WordleEdit.h"
#include <QComboBox>
#include <QRegularExpressionValidator>

WordleWidget::WordleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldeWidget)
{
    ui->setupUi(this);
}

WordleWidget::~WordleWidget()
{
    deleteAll();
    delete ui;
}

/**
 * @brief WordleWidget::deleteAll
 * Delete all items in containers
 * and clear lists
 */
void WordleWidget::deleteAll()
{
    qDeleteAll(line_edits);
    qDeleteAll(combo_boxes);
    qDeleteAll(cb_layouts);
    combo_boxes.clear();
    line_edits.clear();
    cb_layouts.clear();
}

/**
 * @brief WordleWidget::reset
 * Clear all fields
 */
void WordleWidget::reset()
{
    foreach(auto cb, combo_boxes)
    {
        cb->setCurrentIndex(0);
    }
    foreach(auto le, line_edits)
    {
        le->clear();
    }
}

/**
 * @brief WordleWidget::configure
 * Configure widget for use with given parameters.
 * @param length word length
 * @param count word count
 */
void WordleWidget::configure(int length, int count)
{
    deleteAll();
    // Create Line Edits for each letter
    for(int i = 0; i < length; ++i)
    {
        WordleEdit *wordleEdit = new WordleEdit;
        line_edits.append(wordleEdit);
        ui->horizontalLayout_letters->addWidget(wordleEdit);
    }

    connectLineEdits();

    // Create Combo Boxes for each letter and each word
    for(int i = 0; i < count; ++i)
    {
        QHBoxLayout *layout = new QHBoxLayout;
        cb_layouts.append(layout);
        ui->verticalLayout_comboBoxes->addLayout(layout);
        for(int j = 0; j < length; ++j)
        {
            QComboBox *cb = new QComboBox;
            cb->addItems(hint_list);
            layout->addWidget(cb);
            combo_boxes.append(cb);
        }
    }
}

/**
 * @brief WordleWidget::useWord
 * Populate widget with <word>
 * @param word
 */
void WordleWidget::useWord(QString word)
{
    if(word.length() == line_edits.size())
    {
        for(int i = 0; i < line_edits.size(); ++i)
        {
            line_edits[i]->setText(word.at(i));
        }
    }
}

/**
 * @brief WordleWidget::on_pushButton_submit_clicked
 * Send out word as a QString and all hints in
 * a 2D list via submitWord signal. Give focus to
 * lineEdit_1.
 */
void WordleWidget::on_pushButton_submit_clicked()
{
    QString word;

    foreach(WordleEdit *we, line_edits)
    {
        word += we->text();
    }

    QList<QList<int>> all_hints;
    QList<int> hints;
    for(int i = 1; i <= combo_boxes.size(); ++i)
    {
        hints << combo_boxes.at(i - 1)->currentIndex();
        if(i % word.length() == 0)
        {
            all_hints << hints;
            hints.clear();
        }
    }

    emit submitWord(word, all_hints);

    line_edits[0]->takeFocus();
}

/**
 * @brief WordleWidget::connectLineEdits
 * Connect Wordle Edits so that typing in one sends focus to the next.
 */
void WordleWidget::connectLineEdits()
{
    for(int i = 1; i < line_edits.size(); ++i)
    {
        connect(line_edits.at(i - 1), &WordleEdit::doneSignal, line_edits.at(i), &WordleEdit::takeFocus);
    }
}


