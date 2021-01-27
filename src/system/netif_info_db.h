/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
*
* Author:      maojj <maojunjie@uniontech.com>
* Maintainer:  maojj <maojunjie@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef NETIF_INFO_DB_H
#define NETIF_INFO_DB_H

#include "netif.h"
#include "netlink.h"

#include <QMultiMap>
#include <QMap>

#include "netif_monitor.h"
#include <memory>

namespace core {
namespace system {

struct netif_stat {
    unsigned long long rx_bytes; // received bytes
    unsigned long long tx_bytes; // transmitted bytes
    char iface[IF_NAMESIZE]; // interface name
};

class NetifInfoDB
{
    enum StatIndex { kLastStat = 0, kCurrentStat = 1, kStatCount = kCurrentStat + 1 };

public:
    explicit NetifInfoDB();
    virtual ~NetifInfoDB() = default;

    QMap<QByteArray, NetifInfoPtr> infoDB();
    void update();
    bool getSockIOStatByInode(ino_t ino, SockIOStat &stat);

protected:
    void update_addr();
    void update_netif_info();

private:
    std::unique_ptr<Netlink> m_netlink;

    QMultiMap<int, INet4Addr> m_addrIpv4DB;
    QMultiMap<int, INet6Addr> m_addrIpv6DB;

    QMap<QByteArray, NetifInfoPtr> m_infoDB;

    QMap<ino_t, SockIOStat> m_sockIOStatMap;


    timeval timevalList[kStatCount] = {timeval{0, 0}, timeval{0, 0}};
    QSharedPointer<struct netif_stat> m_netStat[kStatCount] {{}, {}};
};

inline QMap<QByteArray, NetifInfoPtr> NetifInfoDB::infoDB()
{
    return m_infoDB;
}

} // namespace system
} // namespace core

#endif // NETIF_INFO_DB_H
