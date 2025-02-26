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
#ifndef ICONSMANAGER_H
#define ICONSMANAGER_H

#include <QMap>
#include <QObject>
#include <QPixmap>
#include <memory>

class QToolButton;
class QPushButton;
class IconsManager : public QObject
{
    Q_OBJECT
public:
    using PPixmap = std::shared_ptr<QPixmap>;
    enum IconName {
        GUTTER_SYNTAX_ERROR,
        GUTTER_SYNTAX_WARNING,
        GUTTER_BREAKPOINT,
        GUTTER_ACTIVEBREAKPOINT,
        GUTTER_BOOKMARK,

        PARSER_TYPE,
        PARSER_CLASS,
        PARSER_NAMESPACE,
        PARSER_DEFINE,
        PARSER_ENUM,
        PARSER_GLOBAL_METHOD,
        PARSER_INHERITED_PROTECTED_METHOD,
        PARSER_INHERITED_METHOD,
        PARSER_PROTECTED_METHOD,
        PARSER_PUBLIC_METHOD,
        PARSER_PRIVATE_METHOD,
        PARSER_GLOBAL_VAR,
        PARSER_INHERITED_PROTECTD_VAR,
        PARSER_INHERITED_VAR,
        PARSER_PROTECTED_VAR,
        PARSER_PUBLIC_VAR,
        PARSER_PRIVATE_VAR,

        ACTION_MISC_BACK,
        ACTION_MISC_FORWARD,
        ACTION_MISC_ADD,
        ACTION_MISC_REMOVE,
        ACTION_MISC_GEAR,
        ACTION_MISC_CROSS,
        ACTION_MISC_FOLDER,
        ACTION_MISC_TERM,
        ACTION_MISC_CLEAN,
        ACTION_MISC_VALIDATE,
        ACTION_MISC_RENAME,
        ACTION_MISC_HELP,

        ACTION_FILE_NEW,
        ACTION_FILE_OPEN,
        ACTION_FILE_OPEN_FOLDER,
        ACTION_FILE_SAVE,
        ACTION_FILE_SAVE_AS,
        ACTION_FILE_SAVE_ALL,
        ACTION_FILE_CLOSE,
        ACTION_FILE_CLOSE_ALL,
        ACTION_FILE_PRINT,
        ACTION_FILE_PROPERTIES,
        ACTION_FILE_LOCATE,

        ACTION_PROJECT_NEW,
        ACTION_PROJECT_SAVE,
        ACTION_PROJECT_CLOSE,
        ACTION_PROJECT_NEW_FILE,
        ACTION_PROJECT_ADD_FILE,
        ACTION_PROJECT_REMOVE_FILE,
        ACTION_PROJECT_PROPERTIES,

        ACTION_EDIT_UNDO,
        ACTION_EDIT_REDO,
        ACTION_EDIT_CUT,
        ACTION_EDIT_COPY,
        ACTION_EDIT_PASTE,
        ACTION_EDIT_INDENT,
        ACTION_EDIT_UNINDENT,
        ACTION_EDIT_SEARCH,
        ACTION_EDIT_REPLACE,
        ACTION_EDIT_SEARCH_IN_FILES,
        ACTION_EDIT_SORT_BY_NAME,
        ACTION_EDIT_SORT_BY_TYPE,
        ACTION_EDIT_SHOW_INHERITED,

        ACTION_CODE_BACK,
        ACTION_CODE_FORWARD,
        ACTION_CODE_ADD_BOOKMARK,
        ACTION_CODE_REMOVE_BOOKMARK,
        ACTION_CODE_REFORMAT,

        ACTION_RUN_COMPILE,
        ACTION_RUN_COMPILE_RUN,
        ACTION_RUN_RUN,
        ACTION_RUN_REBUILD,
        ACTION_RUN_OPTIONS,
        ACTION_RUN_DEBUG,
        ACTION_RUN_STEP_OVER,
        ACTION_RUN_STEP_INTO,
        ACTION_RUN_STEP_OUT,
        ACTION_RUN_RUN_TO_CURSOR,
        ACTION_RUN_CONTINUE,
        ACTION_RUN_STOP,
        ACTION_RUN_ADD_WATCH,
        ACTION_RUN_REMOVE_WATCH,
        ACTION_RUN_STEP_OVER_INSTRUCTION,
        ACTION_RUN_STEP_INTO_INSTRUCTION,
        ACTION_RUN_INTERRUPT,

        ACTION_VIEW_MAXIMUM,
        ACTION_VIEW_CLASSBROWSER,
        ACTION_VIEW_FILES,
        ACTION_VIEW_COMPILELOG,
        ACTION_VIEW_BOOKMARK,
        ACTION_VIEW_TODO,

        ACTION_HELP_ABOUT,

        ACTION_PROBLEM_PROBLEM,
        ACTION_PROBLEM_SET,
        ACTION_PROBLEM_PROPERTIES,
        ACTION_PROBLEM_EDIT_SOURCE,
        ACTION_PROBLEM_RUN_CASES
    };
    explicit IconsManager(QObject *parent = nullptr);

    void updateEditorGuttorIcons(const QString& iconSet, int size);
    void updateParserIcons(const QString& iconSet, int size);
    void updateActionIcons(const QString iconSet, int size);

    PPixmap getPixmap(IconName iconName) const;

    QIcon getIcon(IconName iconName) const;

    void setIcon(QToolButton* btn, IconName iconName) const;
    void setIcon(QPushButton* btn, IconName iconName) const;

    PPixmap createSVGIcon(const QString& filename, int width, int height);
    const QSize &actionIconSize() const;

signals:
    void actionIconsUpdated();
private:
    QMap<IconName,PPixmap> mIconPixmaps;
    PPixmap mDefaultIconPixmap;
    QSize mActionIconSize;
};

extern IconsManager* pIconsManager;
#endif // ICONSMANAGER_H
