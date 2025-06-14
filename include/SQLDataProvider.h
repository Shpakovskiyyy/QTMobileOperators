#ifndef SQLDATAPROVIDER_H
#define SQLDATAPROVIDER_H

#include "IDataProvider.h"

class SQLDataProvider : public IDataProvider {

public:
    SQLDataProvider(const QString& inDbPath);
    virtual ~SQLDataProvider() = default;

public:
    virtual QVector<Country> loadData() override;

private:
    QString dbPath;

};

#endif // SQLDATAPROVIDER_H
