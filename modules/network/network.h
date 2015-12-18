#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtPlugin>

#include "interfaces.h"

class QLabel;
class NetworkMainWidget;
class Network: public QObject, ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.deepin.ControlCenter.ModuleInterface" FILE "network.json")
    Q_INTERFACES(ModuleInterface)

public:
    Network();
    ~Network() Q_DECL_OVERRIDE;
    QFrame* getContent() Q_DECL_OVERRIDE;

    ControlCenterProxyInterface *getInterface() const;

signals:
    void dccVisibleChanged(bool visible);

protected:
    void setProxy(ControlCenterProxyInterface *proxy) Q_DECL_OVERRIDE;

private:
    NetworkMainWidget * m_mainWidget;
};

#endif
