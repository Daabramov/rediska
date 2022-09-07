/*
 *  Redis Client Native AddIn
 *  Copyright (C) 2022  Abramov Dmitry
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef SAMPLEADDIN_H
#define SAMPLEADDIN_H
#define NOMINMAX

//#include <sw/redis++/redis++.h>
#include "Component.h"

class RedisClientAddIn final : public Component {
public:
    const char *Version = u8"1.0.0.1";

    RedisClientAddIn();

private:
    std::string extensionName() override;

    void initRedisClient(const variant_t &a);

    variant_t get(const variant_t &a);

    variant_t set(const variant_t &key, const variant_t &val, const variant_t &ttm);

    variant_t hSet(const variant_t &key, const variant_t &field, const variant_t &value);

    variant_t hGet(const variant_t &key, const variant_t &field);

    variant_t del(const variant_t &key);

    variant_t exists(const variant_t &key);

    void flushAll();

    variant_t lpush(const variant_t &key, const variant_t &values, const variant_t &delimiter);

    variant_t lrange(const variant_t &key, const variant_t &start, const variant_t &stop);

};

#endif //SAMPLEADDIN_H
