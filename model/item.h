#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class Item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString cover READ cover WRITE setCover NOTIFY coverChanged)
public:
    explicit Item(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString cover() const;
    void setCover(const QString &cover);

signals:
    void nameChanged();
    void coverChanged();
public slots:
private:
    QString m_name;
    QString m_cover;
};

#endif // ITEM_H
