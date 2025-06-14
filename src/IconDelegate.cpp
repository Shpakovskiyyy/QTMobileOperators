#include "IconDelegate.h"
#include "Paths.h"

#include <QCoreApplication>


static const auto s_dirFormatToItemTypeMap = QMap<StyledItemType, QString>{ { StyledItemType::Country, QString("countries/%1.png") },
                                                                            { StyledItemType::Operator, QString("operators/%1.png") } };


IconDelegate::IconDelegate(QObject *parent) : QStyledItemDelegate{parent}
{}

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto opt = option;
    initStyleOption(&opt, index);

    const auto iconFileNameVar = index.data(Qt::ItemDataRole::DecorationRole);
    if ( !iconFileNameVar.isValid() ) return;
    const auto iconFileName = iconFileNameVar.toString();

    const auto styledItemTypeVar = index.data(Qt::ItemDataRole::DecorationPropertyRole);
    if ( !styledItemTypeVar.isValid() ) return;
    const auto styledItemType = (StyledItemType)styledItemTypeVar.toInt();


    const auto iconDirectoryName = s_dirFormatToItemTypeMap[styledItemType].arg(iconFileName);
    const auto iconPath = Paths::combine( Paths::projectIconsPath(), iconDirectoryName );

    QPixmap pix(iconPath);
    opt.icon = QIcon(pix);

    QStyledItemDelegate::paint(painter, opt, index);
}
