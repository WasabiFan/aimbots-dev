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

#include "terminal_device_stub.hpp"

#include "modm/io/iostream.hpp"

namespace tap::stub
{
bool TerminalDeviceStub::read(char &c)
{
    if (readBuffer.size() == 0)
    {
        c = modm::IOStream::eof;
        return false;
    }
    else
    {
        c = readBuffer.front();
        readBuffer.pop_front();
        return true;
    }
}

void TerminalDeviceStub::write(char c) { writeBuffer.push_back(c); }

void TerminalDeviceStub::flush()
{
    // pass
}

void TerminalDeviceStub::emplaceItemsInReadBuffer(const std::vector<char> &items)
{
    std::move(std::begin(items), std::end(items), std::back_inserter(readBuffer));
}

int TerminalDeviceStub::readItemsFromWriteBuffer(std::vector<char> &items, std::size_t itemsToRead)
{
    for (std::size_t i = 0; i < itemsToRead; i++)
    {
        if (writeBuffer.size() == 0)
        {
            return i;
        }

        items.push_back(writeBuffer.front());
        writeBuffer.pop_front();
    }
    return itemsToRead;
}

}  // namespace tap::stub
