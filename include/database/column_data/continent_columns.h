#pragma once


// Application headers
#include "include/column_data/column_data.h"

namespace ehm_dal::column_data {
// --- Continent column data --- //
/*!
 * \brief The ContinentColumns class sets out the column indexes for the `ehm_dal::schema::Continent` schema
 */
class ContinentColumns : public ehm_dal::column_data::ColumnData
{
public:
    ContinentColumns();

    enum COLUMN_INDEXES {
        Name = FirstStandardDerivedColumnIndex,
        Abbreviation,
        NameContinentality,
        RegionalStrength,
        Gender
    };
};
} // namespace ehm_dal::schema

