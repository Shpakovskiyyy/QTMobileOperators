#ifndef PATHS_H
#define PATHS_H

#include <QString>
#include <QCoreApplication>

class Paths {

public:
    static QString projectDirPath()             { return QCoreApplication::applicationDirPath() + "../../.."; };
    static QString projectResourcesDirPath()    { return projectDirPath() + "/resources"; };
    static QString projectIconsPath()           { return projectResourcesDirPath() + "/icons"; };

public:
    static QString combine(const QString& first, const QString& second) { return first + "/" + second; }

};

#endif // PATHS_H
