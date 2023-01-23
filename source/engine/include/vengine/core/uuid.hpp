/// \file uuid.hpp
/// \brief Head file for UUID
///
/// A detailed file description.
///
/// \author author_name
/// \version version_number
/// \date xxxx-xx-xxx

#ifndef _VENGINE_CORE_UUID_HPP
#define _VENGINE_CORE_UUID_HPP

#pragma once

#include <engine.hpp>
#include <vengine/data/meta.hpp>

namespace vEngine
{
    namespace Core
    {
        // very simple and intuitive uuid generate
        class UUIDGenerator
        {
            friend class Context;
            public:
                constexpr static auto properties()
                {
                    return std::tuple_cat(
                        // GameNode::properties(),
                        std::make_tuple(
                            property("current_id", &UUIDGenerator::current_id_)
                        )
                    );
                }
            private:
                explicit UUIDGenerator() : current_id_(0){};
                UUIDGenerator(const UUIDGenerator& rhs)
                {
                    UNUSED_PARAMETER(rhs);
                };
                UUIDGenerator& operator=(const UUIDGenerator& rhs)
                {
                    if(this != &rhs)
                    {
                        this->current_id_ = rhs.current_id_;
                    }
                    return *this;
                };
                virtual ~UUIDGenerator(){};

                uint64_t current_id_;

            public:
                static UUIDGenerator& GetInstance()
                {
                    static UUIDGenerator Instance;
                    return Instance;
                }
                uint64_t Generate()
                {
                    return ++this->current_id_;
                }
        };

        class UUID
        {
                friend struct std::hash<vEngine::Core::UUID>;
                friend struct GameObjectDescriptor;
                // friend class DebugTracking;
                // friend class Json;

            public:
                virtual ~UUID(void){};

                const uint64_t AsUint() const
                {
                    return this->data_;
                }

                void Set(const uint64_t id)
                {
                    this->data_ = id;
                }

            private:
                UUID() : data_(0)
                {
                    data_ = UUIDGenerator::GetInstance().Generate();
                }

            private:
                explicit UUID(const uint64_t uuid)
                {
                    this->data_ = uuid;
                }

            public:
                UUID(const UUID& rhs)  // copy constructor
                {
                    this->data_ = rhs.data_;
                }

                UUID& operator=(const UUID& rhs)
                {
                    if (this == &rhs) return *this;
                    data_ = rhs.data_;
                    return *this;
                }
                // compare operator
                bool operator==(const UUID& rhs) const
                {
                    return this->data_ == rhs.data_;
                }
                bool operator!=(const UUID& rhs) const
                {
                    return this->data_ != rhs.data_;
                }
                // constexpr static auto properties()
                // {
                //     return std::make_tuple(
                //         property("value", &UUID::data_)
                //     );
                // }

            private:
                uint64_t data_;
        };
    }  // namespace Core
}  // namespace vEngine

namespace std
{
    template <>
    struct hash<vEngine::Core::UUID>
    {
            vEngine::uint64_t operator()(vEngine::Core::UUID const& value) const
            {
                hash<vEngine::uint64_t> HashFunc;
                return HashFunc(value.data_);
            }
    };
}  // namespace std

#endif /* _VENGINE_CORE_UUID_HPP */
