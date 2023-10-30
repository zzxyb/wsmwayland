#ifndef OUTPUTPOWERMANAGEMENT_H
#define OUTPUTPOWERMANAGEMENT_H

#include "wsmwaylandglobal.h"
#include "abstractresource.h"

#include "qwayland-wlr-output-power-management-unstable-v1.h"

#include <QObject>
#include <QScreen>
#include <QQuickItem>

class OutputPowerManagementPrivate;

class LYCHEE_WSMWAYLAND_EXPORT OutputPowerManagement : public AbstractResource, public  QtWayland::zwlr_output_power_manager_v1
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OutputPowerManagement);
    QML_ELEMENT
public:
    enum Mode {
        On = 0,
        Standby = 1,
        Suspend = 2,
        Off = 3,
    };
    Q_ENUM(Mode)

public:
    explicit OutputPowerManagement(QObject *parent = nullptr);
    ~OutputPowerManagement() = default;

    Q_INVOKABLE void forceDpmsMode(Mode mode);
    Q_INVOKABLE void setDpmsMode(Mode mode, QScreen *screen);
    void setDpmsMode(Mode mode, struct ::wl_output *output);

Q_SIGNALS:
    void dpmsModeChanged(Mode mode, QScreen *screen);

protected:
    void addListener() override;
    void removeListener() override;
    OutputPowerManagement(OutputPowerManagementPrivate &dd, QObject *parent = nullptr);
    static void handleListenerGlobal(void *data, wl_registry *registry, uint32_t id, const QString &interface, uint32_t version);

private:
    Q_DISABLE_COPY(OutputPowerManagement)
};

#endif // OUTPUTPOWERMANAGEMENT_H
