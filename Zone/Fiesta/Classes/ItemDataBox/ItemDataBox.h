#pragma once

#include "pch.h"

#include "Pointers.h"
#include "Types.h"

namespace Fiesta::Classes::ItemDataBox
{
    class ItemDataBox
    {
    public:
        SIGNATURE Original_ArrayOperator = reinterpret_cast<Types::t_ArrayOperator>(Pointers::ArrayOperator);
        SIGNATURE Original_ConvertToItemId = reinterpret_cast<Types::t_ToItemId>(Pointers::ConvertToItemId);
    };
}