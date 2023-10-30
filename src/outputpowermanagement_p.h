#ifndef OUTPUTPOWERMANAGEMENT_P_H
#define OUTPUTPOWERMANAGEMENT_P_H

#include "abstractresource_p.h"
#include "outputpowermanagement.h"

class LYCHEE_WSMWAYLAND_EXPORT OutputPowerManagementPrivate : public AbstractResourcePrivate
{
    Q_DECLARE_PUBLIC(OutputPowerManagement)
public:
    OutputPowerManagementPrivate();
};

#endif // OUTPUTPOWERMANAGEMENT_P_H
