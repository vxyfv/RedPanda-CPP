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
#ifndef CODECOMPLETIONPOPUP_H
#define CODECOMPLETIONPOPUP_H

#include <QListView>
#include <QWidget>
#include "parser/cppparser.h"
#include "codecompletionlistview.h"

class ColorSchemeItem;
class CodeCompletionListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit CodeCompletionListModel(const StatementList* statements,QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void notifyUpdated();
    const ColorCallback &colorCallback() const;
    void setColorCallback(const ColorCallback &newColorCallback);

private:
    const StatementList* mStatements;
    ColorCallback mColorCallback;
};

class CodeCompletionPopup : public QWidget
{
    Q_OBJECT

public:
    explicit CodeCompletionPopup(QWidget *parent = nullptr);
    ~CodeCompletionPopup();

    void setKeypressedCallback(const KeyPressedCallback &newKeypressedCallback);
    void prepareSearch(const QString& preWord,
                       const QStringList & ownerExpression,
                       const QString& memberOperator,
                       const QStringList& memberExpression,
                       const QString& filename,
                       int line);
    bool search(const QString& memberPhrase, bool autoHideOnSingleResult);

    PStatement selectedStatement();

    const PCppParser &parser() const;
    void setParser(const PCppParser &newParser);

    int showCount() const;
    void setShowCount(int newShowCount);

    bool onlyGlobals() const;
    void setOnlyGlobals(bool newOnlyGlobals);

    bool recordUsage() const;
    void setRecordUsage(bool newRecordUsage);

    bool showKeywords() const;
    void setShowKeywords(bool newShowKeywords);

    bool showCodeSnippets() const;
    void setShowCodeSnippets(bool newShowCodeIns);

    bool ignoreCase() const;
    void setIgnoreCase(bool newIgnoreCase);

    bool sortByScope() const;
    void setSortByScope(bool newSortByScope);

    bool useCppKeyword() const;
    void setUseCppKeyword(bool newUseCppKeyword);

    const PStatement &currentStatement() const;
    void setCurrentStatement(const PStatement &newCurrentStatement);
    const std::shared_ptr<QHash<StatementKind, std::shared_ptr<ColorSchemeItem> > >& colors() const;
    void setColors(const std::shared_ptr<QHash<StatementKind, std::shared_ptr<ColorSchemeItem> > > &newColors);
    const QString &memberPhrase() const;
    const QList<PCodeSnippet> &codeSnippets() const;
    void setCodeSnippets(const QList<PCodeSnippet> &newCodeSnippets);
private:
    void addChildren(PStatement scopeStatement, const QString& fileName,
                     int line);
    void addStatement(PStatement statement, const QString& fileName, int line);
    void filterList(const QString& member);
    void getCompletionFor(
            const QStringList& ownerExpression,
            const QString& memberOperator,
            const QStringList& memberExpression,
            const QString& fileName,
            int line);
    void getCompletionListForPreWord(const QString& preWord);
    void addKeyword(const QString& keyword);
    bool isIncluded(const QString& fileName);
private:
    CodeCompletionListView * mListView;
    CodeCompletionListModel* mModel;
    QList<PCodeSnippet> mCodeSnippets; //(Code template list)
    //QList<PStatement> mCodeInsStatements; //temporary (user code template) statements created when show code suggestion
    StatementList mFullCompletionStatementList;
    StatementList mCompletionStatementList;
    QSet<QString> mIncludedFiles;
    QSet<QString> mUsings;
    QSet<QString> mAddedStatements;
    QString mMemberPhrase;
    QString mMemberOperator;
    QRecursiveMutex mMutex;
    std::shared_ptr<QHash<StatementKind, std::shared_ptr<ColorSchemeItem> > > mColors;

    PCppParser mParser;
    PStatement mCurrentStatement;
    int mShowCount;
    bool mOnlyGlobals;
    bool mRecordUsage;
    bool mShowKeywords;
    bool mShowCodeSnippets;
    bool mIgnoreCase;
    bool mSortByScope;
    bool mUseCppKeyword;

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

    // QObject interface
public:
    bool event(QEvent *event) override;
    const QString &memberOperator() const;
};

#endif // CODECOMPLETIONPOPUP_H
