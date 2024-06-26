#pragma once


// Application headers
#include "include/database/column_data/private/person_columns.h"

namespace ehm_dal::column_data {
// --- Official column data --- //
/*!
 * \brief The OfficialColumns class sets out the column indexes for the `ehm_dal::schema::Official` schema
 */
class OfficialColumns : public ehm_dal::column_data::PersonColumns
{
public:
    OfficialColumns();

    enum COLUMN_INDEXES {
        ClubCompetition = FirstPersonDerivedColumnIndex,
        CurrentAbility,
        PotentialAbility,
        Reputation,
        AllowingInterference,
        AllowingRoughness,
        Discipline,
        ImportantMatches,
        Pressure,
        Refereeing,
        SkatingLine,
        COLUMN_COUNT
    };
};
} // namespace ehm_dal::column_data

