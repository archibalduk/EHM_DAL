#pragma once

// Application headers
#include "include/database/schema/private/person.h"

// Qt headers
class QDataStream;
#include <memory>

namespace ehm_dal::schema {
//class ContractDetails
class NonPlayerData;
class PlayerData;
//class PlayerInfo;
//class StaffInfo;
class StaffPreferences;

// --- Staff --- //
class Staff : public ehm_dal::schema::Person
{
public:
    Staff();
    ~Staff();

    // Child data
    void addChildItem(std::shared_ptr<AbstractTableItem> item,
                      const ehm_dal::tables::TableIndex child_table) override;
    QVariant childData(const QModelIndex &index,
                       qint32 role,
                       column_data::ColumnData *column_data,
                       const ehm_dal::tables::TableIndex child_table) const override;
    qint32 childItemId(const ehm_dal::tables::TableIndex child_table) const override;
    qint32 childRowCount(const ehm_dal::tables::TableIndex child_table) const override;
    bool setChildData(const QModelIndex &index,
                      const QVariant &value,
                      const qint32 role,
                      std::vector<qint32> &modified_columns,
                      ehm_dal::column_data::ColumnData *column_data,
                      const ehm_dal::tables::TableIndex child_table) override;

    // File i/o
    bool read(QDataStream &in, ehm_dal::database::DatabaseVersion &version) override;
    bool write(QDataStream &out, ehm_dal::database::DatabaseVersion &version) override;

private:
    struct Data;
    std::unique_ptr<Data> data_;

    // Get data
    bool deletable() const override;
    QVariant internalData(const qint32 column, const qint32 role) const override;

    // Initialisation
    bool initInternalData() override;

    // Set data
    bool setInternalData(const qint32 column,
                         const QVariant &value,
                         const qint32 role,
                         std::vector<qint32> &modified_columns) override;
};

} // namespace ehm_dal::schema


