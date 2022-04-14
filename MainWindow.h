#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class WordleWinner;
class SuggestionWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WordleWinner *wordle_winner;
    QMap<QChar, int> scrabble_scores;
    QStringList ignored_words;

    QList<SuggestionWidget*> suggestion_widgets;

    int calculateScrabbleScore(QString word);
    void populateScoreMap();
    void resetApp();

private slots:
    void configure(int length, int count, bool suggest, bool survivle);
    void receiveGuess(QString word, QList<QList<int> > all_hints);
    void receiveRemainingWords(QList<QSet<QString> > words);
    void on_pushButton_reset_clicked();

    // Menu Actions
    void openAboutWindow();
    void openConfigureDialog();
    void quitApplication();
};
#endif // MAINWINDOW_H
