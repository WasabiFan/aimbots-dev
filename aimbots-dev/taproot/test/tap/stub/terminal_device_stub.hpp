/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TERMINAL_DEVICE_STUB_HPP_
#define TERMINAL_DEVICE_STUB_HPP_

#include <queue>

#include "modm/io/iodevice.hpp"

namespace tap
{
class Drivers;
}

namespace tap::stub
{
class TerminalDeviceStub : public modm::IODevice
{
public:
    TerminalDeviceStub(tap::Drivers *) {}

    void initialize() {}

    bool read(char &c) override;

    using IODevice::write;
    void write(char c) override;

    void flush() override;

    /**
     * Testing function. Allows you to fill up the buffer that will be read from
     * via the read function above.
     */
    void emplaceItemsInReadBuffer(const std::vector<char> &items);

    /**
     * Testing function. Allows you to read what is being written to by the
     * write function above.
     *
     * @return The number of items successfully read (less than itemsToRead if
     *      the buffer contains less than itemsToRead)
     */
    int readItemsFromWriteBuffer(std::vector<char> &items, std::size_t itemsToRead);

private:
    std::deque<char> readBuffer;
    std::deque<char> writeBuffer;
};
}  // namespace tap::stub

#endif  // TERMINAL_DEVICE_STUB_HPP_
