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
#ifndef PROJECT_H
#define PROJECT_H

#include <QAbstractItemModel>
#include <memory>
#include "projectoptions.h"
#include "utils.h"

class Project;
class Editor;
class CppParser;

struct FolderNode;
using PFolderNode = std::shared_ptr<FolderNode>;
struct FolderNode {
    QString text;
    std::weak_ptr<FolderNode> parent;
    int unitIndex;
    QList<PFolderNode>  children;
    int level;
};

class ProjectUnit {

public:
    explicit ProjectUnit(Project* parent);
    Project* parent() const;
    void setParent(Project* newParent);
    Editor *editor() const;
    void setEditor(Editor *newEditor);
    const QString &fileName() const;
    void setFileName(QString newFileName);
    bool isNew() const;
    void setNew(bool newNew);
    const QString &folder() const;
    void setFolder(const QString &newFolder);
    bool compile() const;
    void setCompile(bool newCompile);
    bool compileCpp() const;
    void setCompileCpp(bool newCompileCpp);
    bool overrideBuildCmd() const;
    void setOverrideBuildCmd(bool newOverrideBuildCmd);
    const QString &buildCmd() const;
    void setBuildCmd(const QString &newBuildCmd);
    bool link() const;
    void setLink(bool newLink);
    int priority() const;
    void setPriority(int newPriority);
    const QByteArray &encoding() const;
    void setEncoding(const QByteArray &newEncoding);
    bool modified() const;
    void setModified(bool value);
    bool save();

    PFolderNode &node();
    void setNode(const PFolderNode &newNode);

private:
    Project* mParent;
    Editor* mEditor;
    QString mFileName;
    bool mNew;
    QString mFolder;
    bool mCompile;
    bool mCompileCpp;
    bool mOverrideBuildCmd;
    QString mBuildCmd;
    bool mLink;
    int mPriority;
    QByteArray mEncoding;
    PFolderNode mNode;
};

using PProjectUnit = std::shared_ptr<ProjectUnit>;



class ProjectModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit ProjectModel(Project* project, QObject* parent=nullptr);
    void beginUpdate();
    void endUpdate();
private:
    Project* mProject;
    int mUpdateCount;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    QModelIndex getParentIndex(FolderNode * node) const;
    // QAbstractItemModel interface
public:
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    Qt::DropActions supportedDropActions() const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
};

class ProjectTemplate;
class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(const QString& filename, const QString& name,QObject *parent = nullptr);
    ~Project();
    QString directory() const;
    QString executable() const;
    QString makeFileName();
    bool modified() const;
    void setFileName(QString value);
    void setModified(bool value);

    void addFolder(const QString& s);
    PProjectUnit addUnit(const QString& inFileName,
                PFolderNode parentNode,
                bool rebuild);
    void buildPrivateResource(bool forceSave=false);
    void checkProjectFileForUpdate(SimpleIni& ini);
    void closeUnit(int index);
    void createFolderNodes();
    void doAutoOpen();
    bool fileAlreadyExists(const QString& s);
    PFolderNode folderNodeFromName(const QString& name);
    char getCompilerOption(const QString& optionString);
    QString getFolderPath(PFolderNode node);
    int getUnitFromString(const QString& s);
    void incrementBuildNumber();
    int indexInUnits(const QString& fileName) const;
    int indexInUnits(const Editor* editor) const;
    QString listUnitStr(const QChar& separator);
    void loadLayout(); // load all [UnitX]
    void loadOptions(SimpleIni& ini);
    void loadUnitLayout(Editor *e, int index); // load single [UnitX] cursor positions
    PFolderNode makeNewFileNode(const QString& s, bool isFolder, PFolderNode newParent);
    PFolderNode makeProjectNode();
    PProjectUnit  newUnit(PFolderNode parentNode,
                 const QString& customFileName="");
    Editor* openUnit(int index);
    void rebuildNodes();
    bool removeUnit(int index, bool doClose, bool removeFile = false);
    bool removeFolder(PFolderNode node);
    void resetParserProjectFiles();
    void saveAll(); // save [Project] and  all [UnitX]
    void saveLayout(); // save all [UnitX]
    void saveOptions();
    void saveUnitAs(int i, const QString& sFileName, bool syncEditor = true); // save single [UnitX]
    void saveUnitLayout(Editor* e, int index); // save single [UnitX] cursor positions
    bool saveUnits();
    void setCompilerOption(const QString& optionString, char value);
    void sortUnitsByPriority();
    void sortUnitsByAlpha();
    void updateFolders();
    void updateNodeIndexes();
    PFolderNode pointerToNode(FolderNode * p, PFolderNode parent=PFolderNode());
    void setCompilerSet(int compilerSetIndex);

    //void showOptions();
    bool assignTemplate(const std::shared_ptr<ProjectTemplate> aTemplate, bool useCpp);
    //void saveToLog();

    std::shared_ptr<CppParser> cppParser();
    const QString &filename() const;

    const QString &name() const;
    void setName(const QString &newName);

    const PFolderNode &node() const;
    void setNode(const PFolderNode &newNode);

    ProjectOptions &options();

    ProjectModel* model() ;

    const QList<PProjectUnit> &units() const;

signals:
    void nodesChanged();
    void modifyChanged(bool value);
private:
    void open();
    void removeFolderRecurse(PFolderNode node);
    void updateFolderNode(PFolderNode node);
    void updateCompilerSetType();

private:
    QList<PProjectUnit> mUnits;
    ProjectOptions mOptions;
    QString mFilename;
    QString mName;
    bool mModified;
    QStringList mFolders;
    std::shared_ptr<CppParser> mParser;
    QList<PFolderNode> mFolderNodes;
    PFolderNode mNode;
    ProjectModel mModel;
};

#endif // PROJECT_H
