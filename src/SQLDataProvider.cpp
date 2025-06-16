#include "SQLDataProvider.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


SQLDataProvider::SQLDataProvider(const QString& inDbPath) : dbPath(inDbPath) {}

QVector<Country> SQLDataProvider::loadData() {
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if ( !db.open() ) {
        qFatal() << "DB Error: " << db.lastError().text() << "\n";
        return QVector<Country>();
    }

    QMap<QString, Country> countryMap;

    QSqlQuery q("SELECT countries.code as country_code, countries.name AS country_name, countries.mcc AS country_mcc, operators.mnc, operators.name AS operator_name FROM countries LEFT JOIN operators ON countries.mcc = operators.mcc", db);
    while ( q.next() ) {
        const auto countryCode = q.value("country_code").toString();
        const auto countryName = q.value("country_name").toString();
        const auto countryMcc = q.value("country_mcc").toString();
        const auto mnc = q.value("mnc").toString();
        const auto operatorName = q.value("operator_name").toString();

        auto& country = countryMap[countryCode];
        country.code = countryCode;
        country.name = countryName;

        if ( countryMcc.isEmpty() || country.mccs.contains(countryMcc) ) continue;
        country.mccs << countryMcc;

        if ( operatorName.isEmpty() || mnc.isEmpty() ) continue;
        country.operators.append({ operatorName, countryMcc, mnc });
    }

    db.close();
    return countryMap.values();
}
