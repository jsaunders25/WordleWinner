#include "WordleWinner.h"

#include <QFile>
#include <QTextStream>

WordleWinner::WordleWinner(QObject *parent) : QObject(parent)
{
    getAllWords();
}

bool WordleWinner::isAWord(QString word)
{
    return dictionary_.contains(word);
}

void WordleWinner::addGuess(WordleWord word)
{
    for(int i = 0; i < 5; ++i)
    {
        switch(word.hints[i])
        {
        case GREEN : wordHas(word.word[i].toLatin1(), i); break;
        case YELLOW : wordContains(word.word[i].toLatin1(), i, &word); break;
        case GREY : wordDoesNotHave(word.word[i].toLatin1(), i, &word); break;
        default : break;
        }
    }
    emit sendRemainingWords(remaining_);
}

QString WordleWinner::getRemainingWords()
{
    QString remaining_words;
    foreach(QString word, remaining_)
    {
        remaining_words.append(word + "\n");
    }
    return remaining_words;
}

void WordleWinner::reset()
{
    remaining_ = dictionary_;
}

void WordleWinner::wordHas(char letter, int index)
{
    foreach(QString word, remaining_)
    {
        if(word.at(index) != letter)
            remaining_.remove(word);
    }
}

void WordleWinner::wordContains(char letter, int index, WordleWord *w_word)
{
    QString guess = w_word->word;
    int occurences = 0;
    bool found_max = false;

    for(int i = 0; i < guess.length(); ++i)
    {
        if(guess.at(i) == letter && w_word->hints[i] != GREY)
            ++occurences;
        else if(guess.at(i) == letter && w_word->hints[i] == GREY)
            found_max = true;
    }

    foreach(QString word, remaining_)
    {
        if((word.count(letter) < occurences || word.at(index) == letter) ||
                (found_max && word.count(letter) > occurences))
            remaining_.remove(word);
    }
}

void WordleWinner::wordDoesNotHave(char letter, int index, WordleWord *w_word)
{
    QString guess = w_word->word;

    if(guess.count(letter) > 1)
    {
        for(int i = 0; i < guess.length(); ++i)
        {
            wordContains(letter, index, w_word);
            return;
        }
    }

    foreach(QString word, remaining_)
    {
        if(word.contains(letter))
            remaining_.remove(word);
    }
}

void WordleWinner::getAllWords()
{
    QFile word_file(":/Words.txt");
    if(word_file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&word_file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line.length() == 5)
            {
                dictionary_.insert(line);
            }
        }
        word_file.close();
    }
    remaining_ = dictionary_;
}
