#include "outputpowermanagement.h"
#include "abstractresource_p.h"
#include "outputpowermanagement_p.h"

extern "C" {
#include "wayland-wlr-output-power-management-unstable-v1-protocol.c"
}

OutputPowerManagementPrivate::OutputPowerManagementPrivate()
    : AbstractResourcePrivate()
{

}

OutputPowerManagement::OutputPowerManagement(QObject *parent)
    : AbstractResource(*new OutputPowerManagementPrivate(), parent)
{
}

void OutputPowerManagement::forceDpmsMode(Mode mode)
{
    QList<QScreen *>screens = QGuiApplication::screens();
    foreach (QScreen *screen, screens) {
        setDpmsMode(mode, screen);
    }
}

void OutputPowerManagement::setDpmsMode(Mode mode, QScreen *screen)
{
    QtWaylandClient::QWaylandScreen * qScreen= static_cast<QtWaylandClient::QWaylandScreen *> (screen->handle());
    setDpmsMode(mode, qScreen->output());
}

void OutputPowerManagement::setDpmsMode(Mode mode, wl_output *output)
{
    struct ::zwlr_output_power_v1 *outputPower = get_output_power(output);
    zwlr_output_power_v1_set_mode(outputPower, mode);
}

void OutputPowerManagement::addListener()
{
    Q_D(OutputPowerManagement);
    d->waylandDisplay->addRegistryListener(&handleListenerGlobal, this);
}

void OutputPowerManagement::removeListener()
{
    Q_D(OutputPowerManagement);
    d->waylandDisplay->removeListener(&handleListenerGlobal, this);
}

OutputPowerManagement::OutputPowerManagement(OutputPowerManagementPrivate &dd, QObject *parent)
    : AbstractResource(dd, parent)
{
}

void OutputPowerManagement::handleListenerGlobal(void *data, wl_registry *registry, uint32_t id, const QString &interface, uint32_t version)
{
    if (interface == QStringLiteral("org_kde_kwin_dpms_manager")) {
        static_cast<OutputPowerManagement *>(data)->init(registry, id, version);
    }
}
