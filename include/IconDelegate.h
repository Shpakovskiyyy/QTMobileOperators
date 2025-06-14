#ifndef ICONDELEGATE_H
#define ICONDELEGATE_H

#include <QStyledItemDelegate>

enum StyledItemType {
    Country = 0,
    Operator,
    Size
};

class IconDelegate : public QStyledItemDelegate {

public:
    explicit IconDelegate(QObject* parent = nullptr);

public:
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

};

#endif // ICONDELEGATE_H
