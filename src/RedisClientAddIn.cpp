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

//#define NOMINMAX

#include <chrono>
#include <stdexcept>
#include <thread>
#include <sw/redis++/redis.h>
#include <regex>
#include <numeric>

#include "RedisClientAddIn.h"
#include "StringUtils.h"

std::shared_ptr<sw::redis::Redis> redisInstance;

std::string RedisClientAddIn::extensionName() {
    return "RedisClient";
}

RedisClientAddIn::RedisClientAddIn() {

    AddProperty(L"Version", L"ВерсияКомпоненты", [&]() {
        auto s = std::string(Version);
        return std::make_shared<variant_t>(std::move(s));
    });

    AddMethod(L"Connect", L"Подключиться", this, &RedisClientAddIn::initRedisClient);
    AddMethod(L"GET", L"GET", this, &RedisClientAddIn::get);
    AddMethod(L"SET", L"SET", this, &RedisClientAddIn::set, {{2, 0}});
    AddMethod(L"HGET", L"HGET", this, &RedisClientAddIn::hGet);
    AddMethod(L"HSET", L"HSET", this, &RedisClientAddIn::hSet);
    AddMethod(L"DEL", L"DEL", this, &RedisClientAddIn::del);
    AddMethod(L"EXISTS", L"EXISTS", this, &RedisClientAddIn::exists);
    AddMethod(L"FLUSHALL", L"FLUSHALL", this, &RedisClientAddIn::flushAll);
    AddMethod(L"LPUSH", L"LPUSH", this, &RedisClientAddIn::lpush);
    AddMethod(L"LRANGE", L"LRANGE", this, &RedisClientAddIn::lrange, {{1, 0}, {2, -1}});

}

void RedisClientAddIn::initRedisClient(const variant_t &uri) {
    redisInstance = std::make_shared<sw::redis::Redis>(std::get<std::string>(uri));
}

variant_t RedisClientAddIn::set(const variant_t &key, const variant_t &val, const variant_t &ttm) {
    return redisInstance->set(
            std::get<std::string>(key),
            std::get<std::string>(val),
            std::chrono::seconds(std::get<int32_t>(ttm))
    );
}

variant_t RedisClientAddIn::get(const variant_t &a) {
    auto value = redisInstance->get(std::get<std::string>(a));

    if (!value) {
        return UNDEFINED;
    }
    return *value;
}

variant_t RedisClientAddIn::hSet(const variant_t &key, const variant_t &field, const variant_t &value) {
    return redisInstance->hset(
        std::get<std::string>(key),
        std::get<std::string>(field),
        std::get<std::string>(value)
    );
}

variant_t RedisClientAddIn::hGet(const variant_t &key, const variant_t &field) {
    auto result = redisInstance->hget(std::get<std::string>(key), std::get<std::string>(field));

    if (!result) {
        return UNDEFINED;
    }

    return *result;
}

variant_t RedisClientAddIn::del(const variant_t &key) {
    return (int32_t) redisInstance->del(std::get<std::string>(key));

}

variant_t RedisClientAddIn::exists(const variant_t &key) {
    return (int32_t) redisInstance->exists(std::get<std::string>(key));
}

void RedisClientAddIn::flushAll() {
    redisInstance->flushall();
}

variant_t RedisClientAddIn::lpush(const variant_t &key, const variant_t &values, const variant_t &delimiter) {
    auto vecString = StringUtils::split(std::get<std::string>(values), std::get<std::string>(delimiter));
    return (int32_t) redisInstance->rpush(std::get<std::string>(key), vecString.begin(), vecString.end());
}

variant_t RedisClientAddIn::lrange(const variant_t &key, const variant_t &start, const variant_t &stop) {
    std::vector<std::string> vec;
    vec.clear();
    redisInstance->lrange(
            std::get<std::string>(key),
            std::get<int32_t>(start),
            std::get<int32_t>(stop),
            std::back_inserter(vec)
    );

    return StringUtils::join(vec);
}



