#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include <QString>
#include <QVector>

struct Operator {
    QString name;
    QString mcc;
    QString mnc;
};

struct Country {
    QString code;
    QString name;
    QStringList mccs;
    QVector<Operator> operators;
};

class IDataProvider {

public:
    IDataProvider() = default;
    virtual ~IDataProvider() = default;

public:
    virtual QVector<Country> loadData() = 0;

};

#endif // IDATAPROVIDER_H
