#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTreeView>
#include <QStandardItemModel>

#include "IDataProvider.h"
#include "DataProviderFactory.h"
#include "IconDelegate.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow   (parent),
    ui              (std::make_shared<Ui::MainWindow>()),
    treeView        (std::make_shared<QTreeView>(this)),
    model           (std::make_shared<QStandardItemModel>(this)),
    iconDelegate    (std::make_shared<IconDelegate>(this))
{
    ui->setupUi(this);
    setCentralWidget(treeView.get());

    setupModel();

    treeView->setModel(model.get());
    treeView->setHeaderHidden(true);
    treeView->setItemDelegate(iconDelegate.get());

    setWindowTitle("Operators Tree");
    resize(600, 400);
}

void MainWindow::setupModel() {
    auto dataProvider = DataProviderFactory::create();

    const auto countries = dataProvider->loadData();
    for (const auto& country : countries) {
        auto countryItem = new QStandardItem(country.name + " (" + country.code + ")");
        countryItem->setData( country.code, Qt::ItemDataRole::DecorationRole );
        countryItem->setData( StyledItemType::Country, Qt::ItemDataRole::DecorationPropertyRole );

        for (const auto& op : country.operators) {
            auto operatorItem = new QStandardItem(op.name + " (" + op.mcc + "-" + op.mnc + ")");
            operatorItem->setData( QString("%1_%2").arg(op.mcc, op.mnc), Qt::ItemDataRole::DecorationRole );
            operatorItem->setData( StyledItemType::Operator, Qt::ItemDataRole::DecorationPropertyRole );

            countryItem->appendRow(operatorItem);
        }

        model->appendRow(countryItem);
    }
}
