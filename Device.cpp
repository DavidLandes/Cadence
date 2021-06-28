#include "Device.h"

Device::Device(QBluetoothDeviceInfo* device, QObject *parent) : QObject(parent)
  , m_info(device)
{

}

Device::~Device()
{
    // TODO: may need to delete m_info here to prevent mem leak. Make sure it is done being used by other classes.
}

QBluetoothDeviceInfo *Device::info()
{
    return m_info;
}

QString Device::name()
{
    return m_info->name();
}

QString Device::address()
{
    return m_info->address().toString();
}
