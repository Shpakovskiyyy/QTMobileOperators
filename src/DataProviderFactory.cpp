#include "DataProviderFactory.h"
#include "SQLDataProvider.h"
#include "Paths.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>


std::unique_ptr<IDataProvider> DataProviderFactory::create() {
    QFile configFile( Paths::combine(Paths::projectDirPath(), "config.json") );
    if ( !configFile.open(QIODevice::ReadOnly) ) qFatal() << "config.json: Could not open config file at location" << configFile.fileName() << "\n";

    auto doc = QJsonDocument::fromJson( configFile.readAll() );
    auto obj = doc.object();
    auto providerType = obj["provider_type"].toString();

    if ( providerType=="sql" ) {
        auto path = obj["provider_name"].toString();
        return std::make_unique<SQLDataProvider>( Paths::combine(Paths::projectResourcesDirPath(), path) );
    } else {
        qFatal() << "config.json: Unrecognizable provider_type '" << providerType << "'\n";
        return nullptr;
    }
}
