#ifndef WORDLEWINNER_H
#define WORDLEWINNER_H

#include <QObject>
#include <QSet>

class WordleWinner : public QObject
{
    Q_OBJECT
public:
    WordleWinner(QObject *parent = nullptr);

    enum Hints {
        GREEN = 0,
        YELLOW,
        GREY
    };

    struct WordleWord {
        QString word;
        Hints hints[5];
    };

    bool isAWord(QString word);
    void addGuess(WordleWord word);
    QString getRemainingWords();

    void reset();

signals:
    void sendRemainingWords(QSet<QString>);

private:
    void wordHas(char letter, int index);
    void wordContains(char letter, int index, WordleWord *w_word);
    void wordDoesNotHave(char letter, int index, WordleWord *w_word);

    void getAllWords();
    QSet<QString> dictionary_, remaining_;
    QStringList guesses_;
};

#endif // WORDLEWINNER_H
