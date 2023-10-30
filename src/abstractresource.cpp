#include "abstractresource.h"
#include "abstractresource_p.h"

AbstractResourcePrivate::AbstractResourcePrivate()
{

}

AbstractResource::AbstractResource(QObject *parent)
    : QObject(*new AbstractResourcePrivate(), parent)
{
    Q_D(AbstractResource);
    if (QGuiApplication::platformName() == QLatin1String("wayland")) {
        QtWaylandClient::QWaylandIntegration *waylandIntegration = static_cast<QtWaylandClient::QWaylandIntegration *>(QGuiApplicationPrivate::platformIntegration());
        if (!waylandIntegration) {
            qCritical(LYCHEE_WSMWAYLAND) << "failed to obtain QWaylandIntegration object";
        } else {
            d->waylandDisplay = waylandIntegration->display();
            if (!d->waylandDisplay) {
                qCritical(LYCHEE_WSMWAYLAND) << "failed to obtain QWaylandDisplay object";
            } else {
                addListener();
            }
        }
    } else {
        qCritical(LYCHEE_WSMWAYLAND) << "current application is non-wayland client";
    }
}

AbstractResource::~AbstractResource()
{
    Q_D(AbstractResource);
    if (d->waylandDisplay) {
        removeListener();
        d->waylandDisplay = nullptr;
    }
}

bool AbstractResource::inited()
{
    Q_D(AbstractResource);
    d->waylandDisplay;
}

AbstractResource::AbstractResource(AbstractResourcePrivate &dd, QObject *parent)
    : QObject(dd, parent)
{}
