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

namespace vEngine
{
    namespace Core
    {
        // very simple and intuitive uuid generate
        class UUIDGenerator
        {
            private:
                explicit UUIDGenerator() : currentid_(0){};
                UUIDGenerator(const UUIDGenerator& rhs)
                {
                    UNUSED_PARAMETER(rhs);
                };
                UUIDGenerator& operator=(const UUIDGenerator& rhs)
                {
                    UNUSED_PARAMETER(rhs);

                    return *this;
                };
                virtual ~UUIDGenerator(){};

                uint64_t currentid_;

            public:
                static UUIDGenerator& GetInstance()
                {
                    static UUIDGenerator Instance;
                    return Instance;
                }
                uint64_t Generate()
                {
                    return ++this->currentid_;
                }
        };

        class UUID
        {
                friend struct std::hash<vEngine::Core::UUID>;
                friend class GameObject;
                friend class DebugTracking;

            public:
                virtual ~UUID(void){};

            private:
                UUID() : data_(0)
                {
                    data_ = UUIDGenerator::GetInstance().Generate();
                }

            private:
                explicit UUID(uint64_t uuid)
                {
                    UNUSED_PARAMETER(uuid);
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
