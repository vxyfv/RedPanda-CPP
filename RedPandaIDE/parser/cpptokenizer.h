/*
 * Copyright (C) 2020-2022 Roy Qu (royqh1979@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef CPPTOKENIZER_H
#define CPPTOKENIZER_H

#include <QObject>
#include "parserutils.h"

class CppTokenizer
{
public:
    struct Token {
      QString text;
      int line;
    };
    using PToken = std::shared_ptr<Token>;
    using TokenList = QVector<PToken>;
    explicit CppTokenizer();

    void reset();
    void tokenize(const QStringList& buffer);
    void dumpTokens(const QString& fileName);
    const TokenList& tokens();
    PToken operator[](int i);
    int tokenCount();
private:
    void addToken(const QString& sText, int iLine);
    void advance();
    void countLines();
    PToken getToken(int index);

    QString getArguments();
    QString getForInit();
    QString getNextToken(
            bool bSkipParenthesis = false,
            bool bSkipArray = false,
            bool bSkipBlock = false);
    QString getNumber();
    QString getPreprocessor();
    QString getWord(
            bool bSkipParenthesis = false,
            bool bSkipArray = false,
            bool bSkipBlock = false);
    bool isArguments();
    bool isForInit();
    bool isNumber();
    bool isPreprocessor();
    bool isWord();
    void simplify(QString& output);
    void simplifyArgs(QString& output);
    void skipAssignment();
    void skipDoubleQuotes();
    void skipPair(const QChar& cStart, const QChar cEnd, const QSet<QChar>& failChars = QSet<QChar>());
    void skipRawString();
    void skipSingleQuote();
    void skipSplitLine();
    void skipTemplateArgs();
    void skipToEOL();
    void skipToNextToken();
    bool openFile(const QString& fileName);
    bool isLetterChar(const QChar& ch);
    bool isHexChar(const QChar& ch);
    bool isDigitChar(const QChar& ch);
    bool isSpaceChar(const QChar& ch);
    bool isLineChar(const QChar& ch);
    bool isBlankChar(const QChar& ch);
    bool isOperatorChar(const QChar& ch);

    bool currentWordEquals(QChar* wordStart, QChar *wordEnd, const QString& text);

private:
    QStringList mBuffer;
    QString mBufferStr;
    QChar* mStart;
    QChar* mCurrent;
    QChar* mLineCount;
    int mCurrentLine;
    QString mLastToken;
    TokenList mTokenList;
};

#endif // CPPTOKENIZER_H
