#ifndef ABSTRACTRESOURCE_H
#define ABSTRACTRESOURCE_H

#include "wsmwaylandglobal.h"

#include <private/qwaylanddisplay_p.h>

#include <QObject>

class AbstractResourcePrivate;

class LYCHEE_WSMWAYLAND_EXPORT AbstractResource : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractResource);

    Q_PROPERTY(bool inited READ inited)

public:
    explicit AbstractResource(QObject *parent = nullptr);
    ~AbstractResource() override;
    bool inited();

protected:
    virtual void addListener() {};
    virtual void removeListener() {};
    AbstractResource(AbstractResourcePrivate &dd, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(AbstractResource)
};

#endif // ABSTRACTRESOURCE_H
