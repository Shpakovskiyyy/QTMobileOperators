#ifndef DATAPROVIDERFACTORY_H
#define DATAPROVIDERFACTORY_H

#include <memory>

class IDataProvider;

class DataProviderFactory
{

    DataProviderFactory()=delete;

public:
    static std::unique_ptr<IDataProvider> create();

};

#endif // DATAPROVIDERFACTORY_H
