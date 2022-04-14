#include "WordleWinner.h"
#include <QFile>
#include <QTextStream>

WordleWinner::WordleWinner(QObject *parent) : QObject(parent)
{
}

/**
 * @brief WordleWinner::isAWord
 * Check if <word> exists in dictionary.
 * @param word
 * @return
 */
bool WordleWinner::isAWord(QString word)
{
    return dictionary_.contains(word);
}

/**
 * @brief WordleWinner::addGuess
 * Using hints in <word>, run appropriate functions
 * to filter lists of remaining words.
 * @param word
 */
void WordleWinner::addGuess(WordleWord word)
{
    for(int j = 0; j < word.hints.size(); ++j)
    {
        for(int i = 0; i < word.hints.at(j).size(); ++i)
        {
            switch(word.hints.at(j).at(i))
            {
            case GREEN : wordHas(j, word.word[i].toLatin1(), i); break;
            case YELLOW : wordContains(j, word.word[i].toLatin1(), i, &word); break;
            case GREY : wordDoesNotHave(j, word.word[i].toLatin1(), i, &word); break;
            default : break;
            }
        }
    }
    emit sendRemainingWords(remaining_);
}

/**
 * @brief WordleWinner::getRemainingWords
 * @return QStringList in which each QString
 * is a list of remaining words.
 */
QStringList WordleWinner::getRemainingWords()
{
    QStringList words_list;
    foreach(auto list, remaining_)
    {
        QString remaining_words;
        foreach(auto word, list)
        {
            remaining_words.append(word + "\n");
        }
        words_list.append(remaining_words);
    }
    return words_list;
}

/**
 * @brief WordleWinner::configure
 * Configure object for use with given parameters.
 * @param length word length
 * @param count word count
 */
void WordleWinner::configure(int length, int count)
{
    reset();
    getAllWords(length);
    for(int i = 0; i < count; ++i)
    {
        remaining_ << dictionary_;
    }
}

/**
 * @brief WordleWinner::reset
 * Clear containers
 */
void WordleWinner::reset()
{
    dictionary_.clear();
    remaining_.clear();
}

/**
 * @brief WordleWinner::wordHas
 * Filter list of remaining words for <w>.
 * The remaining words must have <letter>
 * at <index>.
 * @param w
 * @param letter
 * @param index
 */
void WordleWinner::wordHas(int w, char letter, int index)
{
    foreach(QString word, remaining_[w])
    {
        if(word.at(index) != letter)
            remaining_[w].remove(word);
    }
}

/**
 * @brief WordleWinner::wordContains
 * Filter list of remaining words for <w>.
 * The remaining words must have <letter>,
 * but not at <index>. Also handles case
 * of multiple occurences of <letter>.
 * @param w
 * @param letter
 * @param index
 * @param w_word
 */
void WordleWinner::wordContains(int w, char letter, int index, WordleWord *w_word)
{
    QString guess = w_word->word;
    int occurences = 0;
    bool found_max = false;

    for(int i = 0; i < guess.length(); ++i)
    {
        if(guess.at(i) == letter && w_word->hints[w][i] != GREY)
            ++occurences;
        else if(guess.at(i) == letter && w_word->hints[w][i] == GREY)
            found_max = true;
    }

    foreach(QString word, remaining_[w])
    {
        if((word.count(letter) < occurences || word.at(index) == letter) ||
                (found_max && word.count(letter) > occurences))
            remaining_[w].remove(word);
    }
}

/**
 * @brief WordleWinner::wordDoesNotHave
 * Filter list of remaining words for <w>.
 * The remaining words must not contain <letter>.
 * @param w
 * @param letter
 * @param index
 * @param w_word
 */
void WordleWinner::wordDoesNotHave(int w, char letter, int index, WordleWord *w_word)
{
    QString guess = w_word->word;
    // More than one occurence of <letter>, handle in wordContains
    if(guess.count(letter) > 1)
    {
        for(int i = 0; i < guess.length(); ++i)
        {
            wordContains(w, letter, index, w_word);
            return;
        }
    }

    foreach(QString word, remaining_[w])
    {
        if(word.contains(letter))
            remaining_[w].remove(word);
    }
}

/**
 * @brief WordleWinner::getAllWords
 * Populate dictionary with words of given length
 * @param length
 */
void WordleWinner::getAllWords(int length)
{
    QFile word_file(":/Words.txt");
    if(word_file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&word_file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line.length() == length)
            {
                dictionary_.insert(line);
            }
        }
        word_file.close();
    }
}
