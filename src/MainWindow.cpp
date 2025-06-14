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
    ui              (new Ui::MainWindow),
    treeView        (new QTreeView(this)),
    model           (new QStandardItemModel(this)),
    iconDelegate    (new IconDelegate(this))
{
    ui->setupUi(this);
    setCentralWidget(treeView);

    setupModel();

    treeView->setModel(model);
    treeView->setHeaderHidden(true);
    treeView->setItemDelegate(iconDelegate);

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

MainWindow::~MainWindow() {
    delete ui;
    delete treeView;
    delete model;
    delete iconDelegate;
}
