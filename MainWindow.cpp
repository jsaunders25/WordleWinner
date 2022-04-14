#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "WordleWinner.h"
#include "ConfigureDialog.h"
#include "SuggestionWidget.h"
#include <algorithm>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Wordle Winner");
    populateScoreMap();

    wordle_winner = new WordleWinner();

    // Menu Actions
    connect(ui->actionAbout,    &QAction::triggered, this, &MainWindow::openAboutWindow);
    connect(ui->actionConfigure,&QAction::triggered, this, &MainWindow::openConfigureDialog);
    connect(ui->actionExit,     &QAction::triggered, this, &MainWindow::quitApplication);

    connect(ui->wordle_widget,  &WordleWidget::submitWord, this, &MainWindow::receiveGuess);
    connect(wordle_winner,      &WordleWinner::sendRemainingWords, this, &MainWindow::receiveRemainingWords);

    // Default Configuration
    configure(5, 1, true, false);
}

MainWindow::~MainWindow()
{
    qDeleteAll(suggestion_widgets);
    delete ui;
    delete wordle_winner;
}

/**
 * @brief MainWindow::calculateScrabbleScore
 * Calculate Scrabble score of <word>. Return the score.
 * @param word
 * @return
 */
int MainWindow::calculateScrabbleScore(QString word)
{
    int score = 0;
    foreach(QChar letter, word)
    {
        score += scrabble_scores.value(letter);
    }
    return score;
}

/**
 * @brief MainWindow::populateScoreMap
 * Populate map matching letters to their Scrabble scores
 */
void MainWindow::populateScoreMap()
{
    scrabble_scores.insert('A', 1);
    scrabble_scores.insert('B', 3);
    scrabble_scores.insert('C', 3);
    scrabble_scores.insert('D', 2);
    scrabble_scores.insert('E', 1);
    scrabble_scores.insert('F', 4);
    scrabble_scores.insert('G', 2);
    scrabble_scores.insert('H', 4);
    scrabble_scores.insert('I', 1);
    scrabble_scores.insert('J', 8);
    scrabble_scores.insert('K', 5);
    scrabble_scores.insert('L', 1);
    scrabble_scores.insert('M', 3);
    scrabble_scores.insert('N', 1);
    scrabble_scores.insert('O', 1);
    scrabble_scores.insert('P', 3);
    scrabble_scores.insert('Q', 10);
    scrabble_scores.insert('R', 1);
    scrabble_scores.insert('S', 1);
    scrabble_scores.insert('T', 1);
    scrabble_scores.insert('U', 1);
    scrabble_scores.insert('V', 4);
    scrabble_scores.insert('W', 4);
    scrabble_scores.insert('X', 8);
    scrabble_scores.insert('Y', 4);
    scrabble_scores.insert('Z', 10);
}

void MainWindow::resetApp()
{
    qDeleteAll(suggestion_widgets);
    suggestion_widgets.clear();
}

/**
 * @brief MainWindow::configure
 * Configure the application to the given parameters.
 * @param length word length
 * @param count word count
 * @param suggest whether to give suggestions
 * @param survivle whether to give Survivle suggestions
 */
void MainWindow::configure(int length, int count, bool suggest, bool survivle)
{
    resetApp();

    ui->wordle_widget->configure(length, count);
    wordle_winner->configure(length, count);
    for(int i = 0; i < count; ++i)
    {
        SuggestionWidget *widget = new SuggestionWidget(suggest, survivle, this);
        connect(widget, &SuggestionWidget::wordClickedSignal, ui->wordle_widget, &WordleWidget::useWord);
        ui->gridLayout_suggestions->addWidget(widget, i / 2, i % 2);
        suggestion_widgets.append(widget);
    }
}

/**
 * @brief MainWindow::receiveGuess
 * Receive guess from the Wordle Widget. Construct a WordleWord struct
 * using <word> and <all_hints> and send to WordleWinner.
 * Append <word> to textBrowser_guesses.
 * @param word
 * @param all_hints
 */
void MainWindow::receiveGuess(QString word, QList<QList<int>> all_hints)
{
    WordleWinner::WordleWord w_word;
    w_word.word = word;
    w_word.hints = all_hints;
    wordle_winner->addGuess(w_word);
    ui->textBrowser_guesses->append(word);
}

/**
 * @brief MainWindow::receiveRemainingWords
 * Receive remaining valid words from WordleWinner.
 * Construct an alphebatized QStringList to display.
 * @param words
 */
void MainWindow::receiveRemainingWords(QList<QSet<QString>> words)
{
    QStringList list;
    QString lowscore_word;
    int lowscore;

    for(int i = 0; i < words.size(); ++i)
    {
        lowscore = 30;
        list.clear();
        lowscore_word.clear();
        foreach(QString word, words[i])
        {
            list << word;
            int score = calculateScrabbleScore(word);
            if(score < lowscore)
            {
                lowscore = score;
                lowscore_word = word;
            }
        }
        std::sort(list.begin(), list.end());
        suggestion_widgets[i]->setRemainingWords(list, lowscore_word);
    }
}

/**
 * @brief MainWindow::on_pushButton_reset_clicked
 * Reset all objects to starting point.
 */
void MainWindow::on_pushButton_reset_clicked()
{
    ui->textBrowser_guesses->clear();
    wordle_winner->reset();
    ui->wordle_widget->reset();
    ignored_words.clear();
    foreach(SuggestionWidget* widget, suggestion_widgets)
    {
        widget->reset();
    }
}

void MainWindow::openAboutWindow()
{
    QMessageBox::about(this,
                       "WordleWinner",
                       "Your greatest ally when playing games like Wordle, Wordle2, and Quordle.");
}

void MainWindow::openConfigureDialog()
{
    ConfigureDialog *dialog = new ConfigureDialog(this);
    connect(dialog, &ConfigureDialog::configurationSignal, this, &MainWindow::configure);
    dialog->exec();
    delete dialog;
}

void MainWindow::quitApplication()
{
    QApplication::quit();
}

