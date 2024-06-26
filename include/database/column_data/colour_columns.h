#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Colour column data --- //
/*!
 * \brief The ColourColumns class sets out the column indexes for the `ehm_dal::schema::Colour` schema
 */
class ColourColumns : public ehm_dal::column_data::ColumnData
{
public:
ColourColumns();

enum COLUMN_INDEXES {
    Name = FirstStandardDerivedColumnIndex,
    Red,
    Green,
    Blue,
    HexCode,
    COLUMN_COUNT
};
};
} // namespace ehm_dal::schema

