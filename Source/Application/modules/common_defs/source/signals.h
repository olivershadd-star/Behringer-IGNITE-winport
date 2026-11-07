/*
* Copyright (C) Musictribe Innovation India Pvt. Ltd
* This file is part of IGNITE.
*
* IGNITE is free software: you can redistribute it and/or modify it under the
* terms of the GNU Affero General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
* more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
*
* SPDX-License-Identifier: AGPL-3.0-or-later
*/
#pragma once

#include <atomic>
#include <cstdint>
#include <functional>
#include <vector>
#define  SIGNALS public
namespace sig
{
    template< class... Args >
    class Signal
    {
    public:
        typedef std::function<void(Args...)> handler_type;
        typedef std::uint64_t id_type;

        id_type connect(handler_type hnd)
        {
            id_type id(next_id());
            handlers.push_back(handler{ id, std::move(hnd) });
            return id;
        }

        bool disconnect(id_type id)
        {
            for (size_t i = 0, n = handlers.size(); i < n; i++)
            {
                if (handlers[i].id == id)
                {
                    handlers.erase(handlers.begin() + i);
                    return true;
                }
            }
            return false;
        }
        //todo implement block and unblock signals
        void block()
        {

        }
        void unblock()
        {

        }
        template <typename T>
        id_type connect(T* inst, void (T::* func)(Args...)) {
            return connect([=](Args... args) {
                (inst->*func)(args...);
                });
        }

        template <typename T>
        int connect(T* inst, void (T::* func)(Args...) const) {
            return connect([=](Args... args) {
                (inst->*func)(args...);
                });
        }

        void emit(Args... args)
        {
            for (auto& h : handlers)
                h.func(args...);
        }

    private:

        struct handler
        {
            id_type id;
            handler_type func;
        };

        std::vector<handler> handlers;

        static id_type next_id()
        {
            static std::atomic<id_type> id(0);
            return ++id;
        }

    };
}
