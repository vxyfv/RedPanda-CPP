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
#ifndef TODOPARSER_H
#define TODOPARSER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QAbstractListModel>

struct TodoItem {
    QString filename;
    int lineNo;
    int ch;
    QString line;
};

using PTodoItem = std::shared_ptr<TodoItem>;

class TodoModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit TodoModel(QObject* parent=nullptr);
    void addItem(const QString& filename, int lineNo,
                 int ch, const QString& line);
    void clear();
    PTodoItem getItem(const QModelIndex& index);
private:
    QList<PTodoItem> mItems;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &parent) const override;
};

class TodoThread: public QThread
{
    Q_OBJECT
public:
    explicit TodoThread(const QString& filename, QObject* parent = nullptr);
signals:
    void parseStarted(const QString& filename);
    void todoFound(const QString& filename, int lineNo, int ch, const QString& line);
    void parseFinished();
private:
    QString mFilename;

    // QThread interface
protected:
    void run() override;
};

using PTodoThread = std::shared_ptr<TodoThread>;

class TodoParser : public QObject
{
    Q_OBJECT
public:
    explicit TodoParser(QObject *parent = nullptr);
    void parseFile(const QString& filename);
    bool parsing() const;

private:
    TodoThread* mThread;
    QRecursiveMutex mMutex;
};

using PTodoParser = std::shared_ptr<TodoParser>;

#endif // TODOPARSER_H
