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
#ifndef SYSTEMCONSTS_H
#define SYSTEMCONSTS_H

#include <QStringList>

#ifndef PREFIX
#define PREFIX "/usr/local"
#endif

#define APP_SETTSINGS_FILENAME "redpandacpp.ini"
#ifdef Q_OS_WIN
#define GCC_PROGRAM     "gcc.exe"
#define GPP_PROGRAM     "g++.exe"
#define GDB_PROGRAM     "gdb.exe"
#define GDB_SERVER_PROGRAM     "gdbserver.exe"
#define GDB32_PROGRAM   "gdb32.exe"
#define MAKE_PROGRAM    "mingw32-make.exe"
#define WINDRES_PROGRAM "windres.exe"
#define GPROF_PROGRAM   "gprof.exe"
#define CLEAN_PROGRAM   "del /q /f"
#define CPP_PROGRAM     "cpp.exe"
#elif defined(Q_OS_LINUX)
#define GCC_PROGRAM     "gcc"
#define GPP_PROGRAM     "g++"
#define GDB_PROGRAM     "gdb"
#define GDB_SERVER_PROGRAM     "gdbserver"
#define GDB32_PROGRAM   "gdb32"
#define MAKE_PROGRAM    "make"
#define WINDRES_PROGRAM ""
#define GPROF_PROGRAM   "gprof"
#define CLEAN_PROGRAM   "rm -rf"
#define CPP_PROGRAM     "cpp"
#else
#error "Only support windows and linux now!"
#endif

#define DEV_PROJECT_EXT "dev"
#define RC_EXT "rc"
#define RES_EXT "res"
#define H_EXT "h"
#define OBJ_EXT "o"
#define DEF_EXT "def"
#define LIB_EXT "a"
#define GCH_EXT "gch"
#define ICON_EXT "ico"
#define TEMPLATE_EXT "template"
#define DEV_INTERNAL_OPEN "$__DEV_INTERNAL_OPEN"
#define DEV_LASTOPENS_FILE "lastopens.ini"
#define DEV_SYMBOLUSAGE_FILE  "symbolusage.json"
#define DEV_CODESNIPPET_FILE  "codesnippets.json"
#define DEV_NEWFILETEMPLATES_FILE "newfiletemplate.txt"
#define DEV_AUTOLINK_FILE "autolink.json"
#define DEV_SHORTCUT_FILE "shortcuts.json"
#define DEV_TOOLS_FILE "tools.json"
#define DEV_BOOKMARK_FILE "bookmarks.json"
#define DEV_BREAKPOINTS_FILE "breakpoints.json"
#define DEV_WATCH_FILE "watch.json"

#ifdef Q_OS_WIN
#   define PATH_SENSITIVITY Qt::CaseInsensitive
#   define PATH_SEPARATOR   ";"
#   define LINE_BREAKER     "\r\n"
#   define NULL_FILE       "NUL"
#   define EXECUTABLE_EXT   "exe"
#   define STATIC_LIB_EXT   "a"
#   define DYNAMIC_LIB_EXT   "dll"
#   define MAKEFILE_NAME    "makefile.win"
#   define ALL_FILE_WILDCARD "*.*"
#elif defined(Q_OS_LINUX)
#   define PATH_SENSITIVITY Qt::CaseSensitive
#   define PATH_SEPARATOR   ":"
#   define LINE_BREAKER     "\n"
#   define NULL_FILE       "/dev/null"
#   define EXECUTABLE_EXT   ""
#   define STATIC_LIB_EXT   "a"
#   define DYNAMIC_LIB_EXT   "d"
#   define MAKEFILE_NAME    "makefile"
#   define ALL_FILE_WILDCARD "*"
#else
#error "Only support windows and linux now!"
#endif

class SystemConsts
{
public:
    SystemConsts();
    const QStringList& defaultFileFilters() const noexcept;
    const QString& defaultCFileFilter() const noexcept;
    const QString& defaultCPPFileFilter() const noexcept;
    const QString& defaultAllFileFilter() const noexcept;
    void addDefaultFileFilter(const QString& name, const QString& fileExtensions);
    const QStringList &iconFileFilters() const;
    const QString& iconFileFilter() const;
    void setIconFileFilters(const QStringList &newIconFileFilters);

    const QStringList &codecNames() const;

private:
    void addFileFilter(QStringList& filters, const QString& name, const QString& fileExtensions);
    QStringList mDefaultFileFilters;
    QStringList mIconFileFilters;
    QStringList mCodecNames;
};

extern SystemConsts* pSystemConsts;
#endif // SYSTEMCONSTS_H
