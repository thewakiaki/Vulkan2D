#pragma once

namespace ClassUtilities{

template<class T>
class ImmutableOwner{
    protected:
        ImmutableOwner() = default;
        ~ImmutableOwner() = default;

    public:
        ImmutableOwner(const ImmutableOwner&) = delete;
        ImmutableOwner(ImmutableOwner&&) = delete;
        ImmutableOwner& operator=(const ImmutableOwner&) = delete;
        ImmutableOwner& operator=(ImmutableOwner&&) = delete;
};

};
