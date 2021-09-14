#include "systemconsts.h"
#include "utils.h"
#include <QObject>
#include <QSet>
#include <QString>
#include <QStringList>
#include <QTextCodec>

SystemConsts* pSystemConsts;

SystemConsts::SystemConsts(): mDefaultFileFilters()
{
    addDefaultFileFilter(QObject::tr("All files"),"*");
    addDefaultFileFilter(QObject::tr("Dev C++ Project files"),"*.dev");
    addDefaultFileFilter(QObject::tr("C files"),"*.c");
    addDefaultFileFilter(QObject::tr("C++ files"),"*.cpp *.cc *.cxx");
    addDefaultFileFilter(QObject::tr("Header files"),"*.h *.hh");

    addFileFilter(mIconFileFilters, QObject::tr("Icon files"), "*.ico");

    mCodecNames.append(ENCODING_AUTO_DETECT);
    mCodecNames.append(ENCODING_SYSTEM_DEFAULT);
    mCodecNames.append(ENCODING_UTF8);
    QStringList codecNames;
    QSet<QByteArray> codecAlias;
    codecAlias.insert("system");
    codecAlias.insert("utf-8");

    foreach (const QByteArray& name, QTextCodec::availableCodecs()){
        QByteArray lname = name.toLower();
        if (lname.startsWith("cp"))
            continue;
        if (codecAlias.contains(lname))
            continue;
        codecNames.append(lname);
        codecAlias.insert(lname);
        QTextCodec* codec = QTextCodec::codecForName(name);
        if (codec) {
            foreach (const QByteArray& alias, codec->aliases()) {
                codecAlias.insert(alias.toLower());
            }
        }
    }
    std::sort(codecNames.begin(),codecNames.end());
    mCodecNames.append(codecNames);
}

const QStringList &SystemConsts::defaultFileFilters() const noexcept
{
    return mDefaultFileFilters;
}

const QString &SystemConsts::defaultCFileFilter() const noexcept
{
    return mDefaultFileFilters[2];
}

const QString &SystemConsts::defaultCPPFileFilter() const noexcept
{
    return mDefaultFileFilters[3];
}

const QString &SystemConsts::defaultAllFileFilter() const noexcept
{
    return mDefaultFileFilters[0];
}

void SystemConsts::addDefaultFileFilter(const QString &name, const QString &fileExtensions)
{
    addFileFilter(mDefaultFileFilters,name,fileExtensions);
}

void SystemConsts::addFileFilter(QStringList filters, const QString &name, const QString &fileExtensions)
{
    filters.append(name+ " (" + fileExtensions+")");
}

const QStringList &SystemConsts::codecNames() const
{
    return mCodecNames;
}

const QStringList &SystemConsts::iconFileFilters() const
{
    return mIconFileFilters;
}

const QString &SystemConsts::iconFileFilter() const
{
    return mIconFileFilters[0];
}

void SystemConsts::setIconFileFilters(const QStringList &newIconFileFilters)
{
    mIconFileFilters = newIconFileFilters;
}
