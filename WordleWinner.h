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
        QList<QList<int>> hints;
    };

    bool isAWord(QString word);
    void addGuess(WordleWord word);
    QStringList getRemainingWords();
    void configure(int length, int count);
    void reset();

signals:
    void sendRemainingWords(QList<QSet<QString>>);

private:
    void wordHas(int w, char letter, int index);
    void wordContains(int w, char letter, int index, WordleWord *w_word);
    void wordDoesNotHave(int w, char letter, int index, WordleWord *w_word);

    void getAllWords(int length);
    QSet<QString> dictionary_;
    QList<QSet<QString>> remaining_;
    QStringList guesses_;
};

#endif // WORDLEWINNER_H
