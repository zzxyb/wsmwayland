#ifndef ABSTRACTRESOURCE_P_H
#define ABSTRACTRESOURCE_P_H

#include "abstractresource.h"

#include <private/qobject_p_p.h>
#include <private/qwaylandwindow_p.h>
#include <private/qwaylandscreen_p.h>
#include <private/qguiapplication_p.h>
#include <private/qwaylandintegration_p.h>

class LYCHEE_WSMWAYLAND_EXPORT AbstractResourcePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(AbstractResource)
public:
    AbstractResourcePrivate();
    QtWaylandClient::QWaylandDisplay *waylandDisplay= nullptr;
};

#endif // ABSTRACTRESOURCE_P_H
